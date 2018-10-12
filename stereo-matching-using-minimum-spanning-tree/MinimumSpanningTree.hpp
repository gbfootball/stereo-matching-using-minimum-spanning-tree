#ifndef MINIMUM_SPANNING_TREE_H
#define MINIMUM_SPANNING_TREE_H

#include <iostream>
#include <vector>

using namespace std;

template <class EdgeType>
class MinimumSpanningTree {
public:
	void addEdge(EdgeType et);
	int getSize() const;
	void getEdgeVector(vector<EdgeType>& v);

private:
	vector<EdgeType> treeEdgeArray_;
	int counter_ = 0;
};

template <class EdgeType>
void MinimumSpanningTree<EdgeType>::addEdge(EdgeType et) {
	treeEdgeArray_.push_back(et);
	counter_++;
}

template <class EdgeType>
int MinimumSpanningTree<EdgeType>::getSize() const {
	return counter_;
}

template <class EdgeType>
void MinimumSpanningTree<EdgeType>::getEdgeVector(vector<EdgeType>& v) {
	for (typename vector<EdgeType>::iterator iter = treeEdgeArray_.begin(); iter != treeEdgeArray_.end(); ++iter) {
		v.push_back(*iter);
	}
}

#endif MINIMUM_SPANNING_TREE_H
