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
			graph_[i][j].weight[LEFT] = j != 0 ? ABS(graph_[i][j].data - graph_[i][j - 1].data) : NONE_WEIGHT;
			graph_[i][j].weight[RIGHT] = j != width_ - 1 ? ABS(graph_[i][j].data - graph_[i][j + 1].data) : NONE_WEIGHT;
			graph_[i][j].weight[UP] = i != 0 ? ABS(graph_[i][j].data - graph_[i + 1][j].data) : NONE_WEIGHT;
			graph_[i][j].weight[DOWN] = i != height_ - 1 ? ABS(graph_[i][j].data - graph_[i - 1][j].data) : NONE_WEIGHT;
		}
	}
}

void FourDirectionGraph::getMinimumSpanningTreeByKruskalAlgorithm(Tree& t) {
	const int numVertex = getVerticesNumber();
	const int numEdges = getEdgesNumber();

	MinHeap<Edge> heap(numEdges);
	UnionFindSet ufSet(numVertex);

	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			Edge edge;

			if (i != height_ - 1) {
				edge.source = pair<int, int>(i, j);
				edge.destination = pair<int, int>(i + 1, j);
				edge.weight = graph_[i][j].weight[DOWN];
				heap.insert(edge);
			}

			if (j != width_ - 1) {
				edge.source = pair<int, int>(i, j);
				edge.destination = pair<int, int>(i, j + 1);
				edge.weight = graph_[i][j].weight[RIGHT];
				heap.insert(edge);
			}
		}
	}

	// iterate n-1 times
	for (int i = 1; i < numVertex; i++) {
		Edge edge;
		heap.remove(edge);

		const pair<int, int> sourcePos = edge.source;
		const pair<int, int> destPos = edge.destination;

		const int u = ufSet.find(sourcePos.first * height_ + sourcePos.second);
		const int v = ufSet.find(destPos.first * height_ + destPos.second);

		// two vertex don't belong to one set which means disconnection
		if (u != v) {
			ufSet.weightedUnion(u, v);
			
		}
	}
}

FourDirectionGraph::~FourDirectionGraph() {
	for (int i = 0; i < height_; i++) {
		delete graph_[i];
	}
	delete graph_;
}
