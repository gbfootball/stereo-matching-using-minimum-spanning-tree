#ifndef UNION_FIND_SET_HPP
#define UNION_FIND_SET_HPP

class UnionFindSet {
	int* parent_;
	int maxSize_;

public:
	explicit UnionFindSet(int size);
	~UnionFindSet();
	int find(int x) const;
	void weightedUnion(int root1, int root2) const;
};

#endif UNION_FIND_SET_HPP
