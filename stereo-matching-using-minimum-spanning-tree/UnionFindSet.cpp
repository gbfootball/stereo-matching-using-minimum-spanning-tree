#include "stdafx.h"
#include "UnionFindSet.h"

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

	// if parent of root1 is not parent of root2
	if (r1 != r2) {
		temp = parent_[r1] + parent_[r2];
	}

	// if children num of r2 (parent of root2) is less than r1's (parent of root1), union r1 to r2
	// if children num of r1 is less than r2's, union r2 to r1
	if (parent_[r2] < parent_[r1]) {
		parent_[r1] = r2;
		parent_[r2] = temp;
	}else {
		parent_[r2] = r1;
		parent_[r1] = temp;
	}

}
