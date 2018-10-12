#ifndef FOUR_DIRECTION_GRAPH_VERTEX_H
#define FOUR_DIRECTION_GRAPH_VERTEX_H

#include <iostream>

using namespace std;

template <class Data>
class FourDirectionGraphVertex {
public:
	pair<int, int> getPosition() const;
	Data getData();
	void setPosition(int row, int col);
	void setData(Data d);

private:
	pair<int, int> pos_;
	Data data_;
};

template <class Data>
pair<int, int> FourDirectionGraphVertex<Data>::getPosition() const {
	return pos_;
}

template <class Data>
Data FourDirectionGraphVertex<Data>::getData() {
	return data_;
}

template <class Data>
void FourDirectionGraphVertex<Data>::setPosition(const int row, const int col) {
	pos_.first = row;
	pos_.second = col;
}

template <class Data>
void FourDirectionGraphVertex<Data>::setData(Data d) {
	data_ = d;
}

#endif FOUR_DIRECTION_GRAPH_VERTEX_H
