#include "stdafx.h"
#include "FourDirectionGraphEdge.hpp"

bool FourDirectionGraphEdge::operator>(const FourDirectionGraphEdge& e) const {
	return weight_ > e.weight_;
}

bool FourDirectionGraphEdge::operator<=(const FourDirectionGraphEdge& e) const {
	return weight_ <= e.weight_;
}

pair<int, int> FourDirectionGraphEdge::getSourcePos() const {
	return sourcePos_;
}

pair<int, int> FourDirectionGraphEdge::getDestPos() const {
	return destPos_;
}

weight_t FourDirectionGraphEdge::getWeight() const {
	return weight_;
}

void FourDirectionGraphEdge::setSourcePos(const int row, const int col) {
	sourcePos_.first = row;
	sourcePos_.second = col;
}

void FourDirectionGraphEdge::setDestPos(const int row, const int col) {
	destPos_.first = row;
	destPos_.second = col;
}

void FourDirectionGraphEdge::setWeight(weight_t w) {
	weight_ = w;
}
