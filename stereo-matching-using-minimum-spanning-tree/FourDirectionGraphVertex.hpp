#ifndef FOUR_DIRECTION_GRAPH_VERTEX_HPP
#define FOUR_DIRECTION_GRAPH_VERTEX_HPP

#include <opencv2/opencv.hpp>

using namespace std;

typedef uchar data_t;

class FourDirectionGraphVertex {
public:
	pair<int, int> getPosition() const;
	data_t getData() const;
	void setPosition(int row, int col);
	void setData(data_t d);

private:
	pair<int, int> pos_;
	data_t data_ = 0;
};

#endif FOUR_DIRECTION_GRAPH_VERTEX_HPP
