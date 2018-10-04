#include"stdafx.h"
#include "FourDirectionGraph.h"

int FourDirectionGraph::getVerticesNumber() const {
	return height_ * width_;
}

int FourDirectionGraph::getEdgesNumber() const {
	return (height_ - 1) * width_ + (width_ - 1) * height_;
}

FourDirectionGraph::FourDirectionGraph(const Mat m) {
	height_ = m.rows;
	width_ = m.cols;

	graph_ = new Vertex*[height_];
	for (int i = 0; i < height_; i++) {
		graph_[i] = new Vertex[width_];
		for (int j = 0; j < width_; j++) {
			graph_[i][j].posRow = i;
			graph_[i][j].posCol = j;
			graph_[i][j].data = m.at<uchar>(i, j);
		}
	}

	// Based on the paper "A Non-Local Cost Aggregation Method for Stereo Matching", 
	// the weight of a pair of neighboring pixels is absolute of value difference between two pixels.

	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			// to the left direction
			graph_[i][j].weight[LEFT] = j != 0 ? ABS(graph_[i][j].data - graph_[i][j - 1].data) : NONE_WEIGHT;
			// to the right direction
			graph_[i][j].weight[RIGHT] = j != width_ - 1 ? ABS(graph_[i][j].data - graph_[i][j + 1].data) : NONE_WEIGHT;
			// to the up direction
			graph_[i][j].weight[UP] = i != 0 ? ABS(graph_[i][j].data - graph_[i + 1][j].data) : NONE_WEIGHT;
			// to the down direction
			graph_[i][j].weight[DOWN] = i != height_ - 1 ? ABS(graph_[i][j].data - graph_[i - 1][j].data) : NONE_WEIGHT;
		}
	}
}

void FourDirectionGraph::getMinimumSpanningTreeByKruskalAlgorithm(Tree& t) {
	const int numVertex = getVerticesNumber();
	const int numEdges = getEdgesNumber();

	MinHeap heap(numEdges);
	UnionFindSet ufSet(numVertex);


}

FourDirectionGraph::~FourDirectionGraph() {
	for (int i = 0; i < height_; i++) {
		delete graph_[i];
	}
	delete graph_;
}
