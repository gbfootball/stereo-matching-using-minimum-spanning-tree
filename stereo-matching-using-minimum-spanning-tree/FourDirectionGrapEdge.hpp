#ifndef FOUR_DIRECTION_GRAPH_EDGE_H
#define FOUR_DIRECTION_GRAPH_EDGE_H

#include <iostream>

using namespace std;

template <class Weight>
class FourDirectionGraphEdge {
public:
	bool operator >(const FourDirectionGraphEdge& e) const;
	bool operator <=(const FourDirectionGraphEdge& e) const;
	pair<int, int> getSourcePos() const;
	pair<int, int> getDestPos() const;
	Weight getWeight();
	void setSourcePos(int row, int col);
	void setDestPos(int row, int col);
	void setWeight(Weight w);

private:
	pair<int, int> sourcePos_;
	pair<int, int> destPos_;
	Weight weight_;
};

template <class Weight>
bool FourDirectionGraphEdge<Weight>::operator >(const FourDirectionGraphEdge& e) const {
	return weight_ > e.weight_;
}

template <class Weight>
bool FourDirectionGraphEdge<Weight>::operator <=(const FourDirectionGraphEdge& e) const {
	return weight_ <= e.weight_;
}

template <class Weight>
pair<int, int> FourDirectionGraphEdge<Weight>::getSourcePos() const {
	return sourcePos_;
}

template <class Weight>
pair<int, int> FourDirectionGraphEdge<Weight>::getDestPos() const {
	return destPos_;
}

template <class Weight>
Weight FourDirectionGraphEdge<Weight>::getWeight() {
	return weight_;
}

template <class Weight>
void FourDirectionGraphEdge<Weight>::setSourcePos(const int row, const int col) {
	sourcePos_.first = row;
	sourcePos_.second = col;
}

template <class Weight>
void FourDirectionGraphEdge<Weight>::setDestPos(const int row, const int col) {
	destPos_.first = row;
	destPos_.second = col;
}

template <class Weight>
void FourDirectionGraphEdge<Weight>::setWeight(Weight w) {
	weight_ = w;
}

#endif FOUR_DIRECTION_GRAPH_EDGE_H
