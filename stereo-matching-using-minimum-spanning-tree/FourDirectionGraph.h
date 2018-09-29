#ifndef FOUR_DIRECTION_GRAPH
#define FOUR_DIRECTION_GRAPH

#include <opencv2/opencv.hpp>

using namespace cv;

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define ABS(x) ((x) < 0 ? -(x) : (x))

struct Vertex {
	int posRow;
	int posCol;
	unsigned char data;
	int weight[4];
};

class FourDirectionGraph {
	Vertex** graph_;
	int height_;
	int width_;

public:
	explicit FourDirectionGraph(Mat m);


	~FourDirectionGraph();
};

#endif FOUR_DIRECTION_GRAPH
