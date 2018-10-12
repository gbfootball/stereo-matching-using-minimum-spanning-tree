#ifndef FOUR_DIRECTION_GRAPH
#define FOUR_DIRECTION_GRAPH

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "FourDirectionGraphVertex.hpp"
#include "FourDirectionGrapEdge.hpp"
#include "FourDirectionGraph.hpp"
#include "MinimumSpanningTree.hpp"

using namespace cv;
using namespace std;

class FourDirectionGraph {
	vector<FourDirectionGraphVertex<uchar>> vertexArray_;
	vector<FourDirectionGraphEdge<int>> edgeRowArray_;
	vector<FourDirectionGraphEdge<int>> edgeColArray_;
	int height_;
	int width_;
	int numVertex_;
	int numEdge_;

public:
	explicit FourDirectionGraph(Mat m);
	void getMinimumSpanningTreeByKruskalAlgorithm(MinimumSpanningTree<FourDirectionGraphEdge<int>>& mst);
};

#endif
