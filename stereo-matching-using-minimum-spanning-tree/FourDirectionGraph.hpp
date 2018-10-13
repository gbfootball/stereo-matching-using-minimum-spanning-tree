#ifndef FOUR_DIRECTION_GRAPH_HPP
#define FOUR_DIRECTION_GRAPH_HPP

#include <vector>

#include <opencv2/opencv.hpp>

#include "FourDirectionGraphVertex.hpp"
#include "MinimumSpanningTree.hpp"
#include "FourDirectionGraphEdge.hpp"

using namespace std;
using namespace cv;

class FourDirectionGraph {
	vector<FourDirectionGraphVertex> vertexArray_;
	vector<FourDirectionGraphEdge> edgeRowArray_;
	vector<FourDirectionGraphEdge> edgeColArray_;
	int height_;
	int width_;
	int numVertex_;
	int numEdge_;

public:
	FourDirectionGraph();
	explicit FourDirectionGraph(Mat m);
	void getMinimumSpanningTreeByKruskalAlgorithm(MinimumSpanningTree& mst);
	FourDirectionGraphVertex getVertex(int row, int col);
};

#endif FOUR_DIRECTION_GRAPH_HPP
