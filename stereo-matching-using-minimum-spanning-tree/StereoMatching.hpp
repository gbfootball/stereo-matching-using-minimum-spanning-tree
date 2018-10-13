#ifndef STEREO_MATCHING_HPP
#define STEREO_MATCHING_HPP

#include <vector>
#include <opencv2/opencv.hpp>

#include "MinimumSpanningTree.hpp"
#include "FourDirectionGraph.hpp"
#include "Tree.hpp"

struct TreeNode;
using namespace std;
using namespace cv;

const int disparityNum = 24;
const int costWindowSize = 2;
const float sigma = 0.1;

class StereoMatching {
public:
	StereoMatching(const Mat& leftImage, const Mat& rightImage);
	void stereoMatchByMinimumSpanningTree(Mat& disparity, double& time);

private:
	Mat leftImage_;
	Mat rightImage_;
	Size imageSize_;
	FourDirectionGraph fourDirectionGraph_;
	MinimumSpanningTree mst_;
	vector<vector<vector<float>>> costSpace_;
	vector<vector<vector<float>>> leftToRootAggregatedCostSpace_;
	vector<vector<vector<float>>> aggregatedCostSpace_;
	Tree tree_;

	float calculateMatchingCost(Point2d leftPoint, Point2d rightPoint, int size);
	void calculateMatchingCostSpace();
	void aggregateCost();
	void leafToRootAggregateCost();
	float calculateLeafToRootAggregateCost(TreeNode* pTreeNode, int disparityLevel);
	void rootToLeafAggregationCost();
	void computeDisparity(Mat& disparity);

	float calculateSimilarityBetweenNode(pair<int, int> pos1, pair<int, int> pos2) const;
	void buildTree();
};

#endif STEREO_MATCHING_HPP
