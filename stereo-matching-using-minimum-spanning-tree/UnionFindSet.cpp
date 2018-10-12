#include "stdafx.h"
#include "UnionFindSet.hpp"

UnionFindSet::UnionFindSet(const int size) {
	maxSize_ = size;
	parent_ = new int[maxSize_];
	for (int i = 0; i < maxSize_; i++) {
		parent_[i] = -1;
	}
}

UnionFindSet::~UnionFindSet() {
	delete parent_;
}

int UnionFindSet::find(int x) const {
	while (parent_[x] >= 0) {
		x = parent_[x];
	}
	return x;
}

void UnionFindSet::weightedUnion(const int root1, const int root2) const {
	const int r1 = find(root1);
	const int r2 = find(root2);
	int temp = 0;

	/*
	 * If parent of root1 is not same with parent of root2 which means they don't belong to one set, we need to union them into one
	 * root node. So we record the new parent index of parent of root1 and parent of root2 in "temp".
	 * 
	 * Indeed, the new parent index is the number of nodes in unioned tree, because the new root node don't have parent, so the index 
	 * is represented as the number of children nodes. 
	 */
	if (r1 != r2) {
		temp = parent_[r1] + parent_[r2];
	}

	/*
	 * If children number of r2 (parent of root2) is less than r1's (parent of root1), we union r1 to r2.
	 * 
	 * Otherwise, we unioning r2 to r1.
	 * 
	 * Then, we can avoid union operation on highing the height of the tree consistently which can make tree more balanced.
	 */
	if (parent_[r2] < parent_[r1]) {
		parent_[r1] = r2;
		parent_[r2] = temp;
	}else {
		parent_[r2] = r1;
		parent_[r1] = temp;
	}

}
