#include "stdafx.h"
#include "StereoMatching.hpp"

StereoMatching::StereoMatching(const Mat& leftImage, const Mat& rightImage) {
	leftImage_ = leftImage;
	rightImage_ = rightImage;
	imageSize_ = Size(leftImage.rows, leftImage.cols);

	costSpace_.resize(imageSize_.height);
	for (int i = 0; i < imageSize_.height; i++) {
		costSpace_[i].resize(imageSize_.width);
		for (int j = 0; j < imageSize_.width; j++) {
			costSpace_[i][j].resize(disparityNum);
		}
	}
}

void StereoMatching::stereoMatchByMinimumSpanningTree(Mat& disparity, double& time) {
	const clock_t start = clock();

	fourDirectionGraph_ = FourDirectionGraph(leftImage_);
	calculateMatchingCostSpace();
	fourDirectionGraph_.getMinimumSpanningTreeByKruskalAlgorithm(mst_);
	buildTree();
	aggregateCost();

	cout << caluculateSimilarityBetweenNode(pair<int, int>(0, 0), pair<int, int>(0, 1)) << endl;

	const clock_t end = clock();
	time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

float StereoMatching::calculateMatchingCost(const Point2d leftPoint, const Point2d rightPoint, const int size) {
	/*
	 * ZNCC means Zero-mean Normalized Cross-Correlation.
	 * 
	 * We assume that
	 *     1. different between left point and its average in window  --> l;
	 *     2. different between right point and its average in window --> r.
	 * Then
	 *     1. "ll" means self-correlation of "l";
	 *     2. "rr" means self-correlation of "r";
	 *     3. "lr" means cross-correlation between "l" and "r".
	 */
	float cost, leftAverage = 0, rightAverage = 0;
	const int sizeWindow = (2 * size + 1) * (2 * size + 1);

	if (leftPoint.x - size >= 0 && leftPoint.x + size < imageSize_.width &&
		leftPoint.y - size >= 0 && leftPoint.y - size < imageSize_.height &&
		rightPoint.x - size >= 0 && rightPoint.x + size < imageSize_.width &&
		rightPoint.y - size >= 0 && rightPoint.y + size < imageSize_.height) {
		for (int i = -size; i < size; i++) {
			for (int j = -size; j < size; j++) {
				const float leftPixelVal = leftImage_.at<uchar>(leftPoint.y + i, leftPoint.x + i);
				const float rightPixelVal = rightImage_.at<uchar>(rightPoint.y + i, rightPoint.x + i);
				leftAverage += leftPixelVal / sizeWindow;
				rightAverage += rightPixelVal / sizeWindow;
			}
		}

		float ll = 0, lr = 0, rr = 0;
		for (int i = -size; i < size; i++) {
			for (int j = -size; j < size; j++) {
				const float leftPixelVal = leftImage_.at<uchar>(leftPoint.y + i, leftPoint.x + i);
				const float rightPixelVal = rightImage_.at<uchar>(rightPoint.y + i, rightPoint.x + i);

				ll += (leftPixelVal - leftAverage) * (leftPixelVal - leftAverage);
				rr += (rightPixelVal - rightAverage) * (rightPixelVal - rightAverage);
				lr += (leftPixelVal - leftAverage) * (rightPixelVal - rightAverage);
			}
		}

		cost = fabs(lr / sqrt(ll * rr));
	} else {
		cost = 100;
	}

	return cost;
}

void StereoMatching::calculateMatchingCostSpace() {
	for (int y = 0; y < imageSize_.height; y++) {
		for (int x = 0; x < imageSize_.width; x++) {
			for (int d = 0; d < disparityNum; d++) {
				costSpace_[y][x][d] = calculateMatchingCost(Point2d(y, x), Point2d(y, x - d), costWindowSize);
			}
		}
	}
}

void StereoMatching::aggregateCost() {
	leafToRootAggregateCost();


}

void StereoMatching::leafToRootAggregateCost() {
	for (int i = 0; i < disparityNum; i++) {
		TreeNode* p = tree_.getRoot();
		leftToRootAggregatedCostSpace_[p->pos.first][p->pos.second][i] = caluculateLeafToRootAggregateCost(p, i);
	}
}

float StereoMatching::caluculateLeafToRootAggregateCost(TreeNode* pTreeNode, const int disparityLevel) {
	const pair<int, int> pos = pTreeNode->pos;
	float leftToRootAggregatedCost = costSpace_[pos.first][pos.second][disparityLevel];

	if (pTreeNode->vChildNode.size() != 0) {
		for (vector<TreeNode*>::iterator iter = pTreeNode->vChildNode.begin(); iter != pTreeNode->vChildNode.end(); ++iter) {
			const float similarity = caluculateSimilarityBetweenNode(pos, (*iter)->pos);
			const float cost = caluculateLeafToRootAggregateCost(*iter, disparityLevel);
			leftToRootAggregatedCost += similarity * cost;
		}
	}

	leftToRootAggregatedCostSpace_[pos.first][pos.second][disparityLevel] = leftToRootAggregatedCost;
	return leftToRootAggregatedCost;
}

float StereoMatching::caluculateSimilarityBetweenNode(const pair<int, int> pos1, const pair<int, int> pos2) const {
	vector<FourDirectionGraphEdge> vEdges = mst_.getTreeEdgeArray();
	for (vector<FourDirectionGraphEdge>::iterator iter = vEdges.begin(); iter != vEdges.end(); ++iter) {
		const pair<int, int> sp = iter->getSourcePos();
		const pair<int, int> dp = iter->getDestPos();

		if (sp == pos1 && dp == pos2 || sp == pos2 && dp == pos1) {
			return exp(-iter->getWeight() / sigma);
		}
	}

	return -1;
}

void StereoMatching::buildTree() {
	queue<TreeNode*> qTreeNode;
	vector<FourDirectionGraphEdge> vEdges = mst_.getTreeEdgeArray();

	tree_ = Tree(mst_.findMinHeightTreeRootNodePos());
	qTreeNode.push(tree_.getRoot());

	while (vEdges.size() > 0 && qTreeNode.size() > 0) {
		TreeNode* p = qTreeNode.front();
		qTreeNode.pop();

		vector<FourDirectionGraphEdge>::iterator iter = vEdges.begin();
		while (iter != vEdges.end()) {
			const pair<int, int> sp = iter->getSourcePos();
			const pair<int, int> dp = iter->getDestPos();

			if (sp == p->pos) {
				TreeNode* pNewNode = Tree::addChildNode(p, dp, iter->getWeight());
				vEdges.erase(iter);
				qTreeNode.push(pNewNode);
			} else if (dp == p->pos) {
				TreeNode* pNewNode = Tree::addChildNode(p, sp, iter->getWeight());
				vEdges.erase(iter);
				qTreeNode.push(pNewNode);
			} else {
				++iter;
			}
		}
	}
}
