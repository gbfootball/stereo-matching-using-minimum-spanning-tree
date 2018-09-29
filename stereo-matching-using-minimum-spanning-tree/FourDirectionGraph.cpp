#include"stdafx.h"
#include "FourDirectionGraph.h"


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

	/*
	 * Based on the paper "A Non-Local Cost Aggregation Method for Stereo Matching", 
	 * the weight of a pair of neighboring pixels is absolute of value difference between two pixels.
	 */
	
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			// to the left direction
			if (j != 0) {
				graph_[i][j].weight[LEFT] = ABS(graph_[i][j].data - graph_[i][j - 1].data);
			}

			// to the right direction
			if (j != width_ - 1) {
				graph_[i][j].weight[RIGHT] = ABS(graph_[i][j].data - graph_[i][j + 1].data);
			}

			// to the up direction
			if (i != 0) {
				graph_[i][j].weight[UP] = ABS(graph_[i][j].data - graph_[i + 1][j].data);
			}

			// to the down direction
			if (i != 0) {
				graph_[i][j].weight[DOWN] = ABS(graph_[i][j].data - graph_[i - 1][j].data);
			}
		}
	}
}

FourDirectionGraph::~FourDirectionGraph() {
	for (int i = 0; i < height_; i++) {
		delete graph_[i];
	}
	delete graph_;
}
