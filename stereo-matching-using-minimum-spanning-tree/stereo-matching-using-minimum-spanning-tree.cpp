#include "stdafx.h"

int main() {
	/*vector<TestDataInfo> testDataset;
	initializeTestDataset(testDataset);

	for (vector<TestDataInfo>::iterator iter = testDataset.begin(); iter != testDataset.end(); ++iter) {
		const Mat leftImage = imread(iter->leftImagePath, GRAY_SCALE_IMAGE);
		const Mat rightImage = imread(iter->rightImagePath, GRAY_SCALE_IMAGE);
		Mat disparityResult;

		// TODO: some function used to implement strero mathcing and return a Mat called "disparityResult"

		// tanslate the referenced (left) image Mat to the four-direction-graph
		FourDirectionGraph fourDirectionGraph(leftImage);

		imwrite(iter->resultPath, disparityResult);
	}*/

	Mat m(3, 3, CV_8S);
	m.at<uchar>(0, 0) = 10;
	m.at<uchar>(0, 1) = 4;
	m.at<uchar>(0, 2) = 16;
	m.at<uchar>(1, 0) = 128;
	m.at<uchar>(1, 1) = 26;
	m.at<uchar>(1, 2) = 64;
	m.at<uchar>(2, 0) = 1;
	m.at<uchar>(2, 1) = 2;
	m.at<uchar>(2, 2) = 4;

	FourDirectionGraph g(m);
	MinimumSpanningTree<FourDirectionGraphEdge<int>> mst;
	vector<FourDirectionGraphEdge<int>> edgeVector;

	g.getMinimumSpanningTreeByKruskalAlgorithm(mst);
	mst.getEdgeVector(edgeVector);

	cout << "The number of edges in the MST is " << mst.getSize() << endl << endl;

	for (vector<FourDirectionGraphEdge<int>>::iterator iter = edgeVector.begin(); iter != edgeVector.end(); ++iter) {
		const pair<int, int> sp = iter->getSourcePos();
		const pair<int, int> dp = iter->getDestPos();
		const int w = iter->getWeight();

		cout << "Edge: ";
		cout << "source position: (" << sp.first << ", " << sp.second << "); ";
		cout << "destination position: (" << dp.first << ", " << dp.second << "); ";
		cout << "weight: " << w << ". " << endl;
	}

	waitKey();
	return 0;
}
