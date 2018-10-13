#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include <vector>
#include <opencv2/opencv.hpp>

#include "FourDirectionGraphEdge.hpp"

using namespace std;

class MinimumSpanningTree {
public:
	void addEdge(FourDirectionGraphEdge e);
	int getSize() const;
	pair<int, int> findMinHeightTreeRootNodePos();
	vector<FourDirectionGraphEdge> getTreeEdgeArray() const;

private:
	vector<FourDirectionGraphEdge> treeEdgeArray_;
	int counter_ = 0;
};

#endif MINIMUM_SPANNING_TREE_HPP
