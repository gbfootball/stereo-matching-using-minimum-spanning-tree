#include "stdafx.h"
#include "FourDirectionGraphVertex.hpp"

pair<int, int> FourDirectionGraphVertex::getPosition() const {
	return pos_;
}

data_t FourDirectionGraphVertex::getData() const {
	return data_;
}

void FourDirectionGraphVertex::setPosition(const int row, const int col) {
	pos_.first = row;
	pos_.second = col;
}

void FourDirectionGraphVertex::setData(data_t d) {
	data_ = d;
}
