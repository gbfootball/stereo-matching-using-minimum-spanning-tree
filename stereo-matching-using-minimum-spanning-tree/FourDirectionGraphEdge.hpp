#ifndef FOUR_DIRECTION_GRAPH_EDGE_HPP
#define FOUR_DIRECTION_GRAPH_EDGE_HPP

#include <iostream>

using namespace std;

typedef int weight_t;

class FourDirectionGraphEdge {
public:
	bool operator >(const FourDirectionGraphEdge& e) const;
	bool operator <=(const FourDirectionGraphEdge& e) const;
	pair<int, int> getSourcePos() const;
	pair<int, int> getDestPos() const;
	weight_t getWeight() const;
	void setSourcePos(int row, int col);
	void setDestPos(int row, int col);
	void setWeight(weight_t w);

private:
	pair<int, int> sourcePos_;
	pair<int, int> destPos_;
	weight_t weight_ = -1;
};

#endif FOUR_DIRECTION_GRAPH_EDGE_HPP
