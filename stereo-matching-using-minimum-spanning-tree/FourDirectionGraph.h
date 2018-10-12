#ifndef FOUR_DIRECTION_GRAPH
#define FOUR_DIRECTION_GRAPH

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "FourDirectionGraphVertex.h"
#include "FourDirectionGrapEdge.h"
#include "FourDirectionGraph.h"
#include "MinimumSpanningTree.h"

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

#endif FOUR_DIRECTION_GRAPH
