#include "stdafx.h"
#include "FourDirectionGraph.hpp"
#include "UnionFindSet.hpp"
#include "MinHeap.hpp"

FourDirectionGraph::FourDirectionGraph(const Mat m) {
	height_ = m.rows;
	width_ = m.cols;

	numVertex_ = height_ * width_;
	numEdge_ = (height_ - 1) * width_ + (width_ - 1) * height_;

	for (int i = 0; i < numVertex_; i++) {
		FourDirectionGraphVertex<uchar> v;
		const int row = i / width_;
		const int col = i % width_;

		v.setPosition(row, col);
		v.setData(m.at<uchar>(row, col));

		vertexArray_.push_back(v);
	}

	/* 
	 * Reference:
	 *     Based on the paper "A Non-Local Cost Aggregation Method for Stereo Matching", 
	 *     the weight of a pair of neighboring pixels is absolute of value difference between two pixels.
	 */

	/*
	 * The "row edge" means horizontal edges. One row contains "width_ - 1" "row edge". They're totally "height_" rows.
	 * The "col edge" means vertical edges. One row contains "width_" "col edge". They're totally "height_ - 1" rows.
	 */
	const int numRowEdge = width_ * (height_ - 1);
	const int numColEdge = (width_ - 1) * height_;

	/*
	 * For each "row edge", mode for calculating position is "width_ - 1" because of "width_ - 1" edges in one row.
	 * For each "col edge", mode for calculating position is "width_" because of "width_" edges in one row.
	 * 
	 * The source vertex is what have same position of edge. 
	 * And the destination vertex is the right position of source vertex for "row edge" while the down position for "col edge".
	 */
	for (int i = 0; i < numRowEdge; i++) {
		FourDirectionGraphEdge<int> e;
		const int row = i / (width_ - 1);
		const int col = i % (width_ - 1);
		const uchar sourceData = vertexArray_[row * width_ + col].getData();
		const uchar destData = vertexArray_[row * width_ + col + 1].getData();

		e.setSourcePos(row, col);
		e.setDestPos(row, col + 1);
		e.setWeight(abs(sourceData - destData));

		edgeRowArray_.push_back(e);
	}

	for (int i = 0; i < numColEdge; i++) {
		FourDirectionGraphEdge<int> e;
		const int row = i / width_;
		const int col = i % width_;
		const uchar sourceData = vertexArray_[row * width_ + col].getData();
		const uchar destData = vertexArray_[(row + 1) * width_ + col].getData();

		e.setSourcePos(row, col);
		e.setDestPos(row + 1, col);
		e.setWeight(abs(sourceData - destData));

		edgeColArray_.push_back(e);
	}
}

void FourDirectionGraph::getMinimumSpanningTreeByKruskalAlgorithm(MinimumSpanningTree<FourDirectionGraphEdge<int>>& mst) {
	MinHeap<FourDirectionGraphEdge<int>> heap(numEdge_);
	UnionFindSet ufSet(numVertex_);

	// add all the edges into min heap
	for (vector<FourDirectionGraphEdge<int>>::iterator iter = edgeRowArray_.begin(); iter != edgeRowArray_.end(); ++iter) {
		heap.insert(FourDirectionGraphEdge<int>(*iter));
	}

	for (vector<FourDirectionGraphEdge<int>>::iterator iter = edgeColArray_.begin(); iter != edgeColArray_.end(); ++iter) {
		heap.insert(FourDirectionGraphEdge<int>(*iter));
	}

	/*
	 * For a MST with n nodes, we just need to get (n - 1) suitable edges to build a tree. So we just need to iterate (n - 1) times.
	 *
	 * Step:
	 *     1. Get one edge with minimum weight by mim heap;
	 *     2. Get the root indices of UFSets which contains two vertices of the edge respectively;
	 *     3. If the indices is not equivalent, two vertices of the edge don't belong to the same set which means two vertices is
	 *        not connected. Then, we insert this edge into MST.
	 *     4. If the indices is equivalent, two vertices of the edge is connected. Then we give up the edge.
	 */
	int count = 1;
	while (count < numVertex_) {
		FourDirectionGraphEdge<int> edge;
		heap.remove(edge);

		const pair<int, int> sourcePos = edge.getSourcePos();
		const pair<int, int> destPos = edge.getDestPos();

		const int u = ufSet.find(sourcePos.first * width_ + sourcePos.second);
		const int v = ufSet.find(destPos.first * width_ + destPos.second);

		if (u != v) {
			ufSet.weightedUnion(u, v);
			mst.addEdge(edge);
			count++;
		}
	}
}
