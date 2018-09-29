#ifndef FOUR_DIRECTION_GRAPH
#define FOUR_DIRECTION_GRAPH

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define NONE_WEIGHT -1

#define ABS(x) ((x) < 0 ? -(x) : (x))

struct Vertex {
	int posRow;
	int posCol;
	uchar data;
	int weight[4];
};

struct Edge {
	pair<int, int> source;
	pair<int, int> destination;
	int weight;
};

struct TreeNode {
	uchar data;
	vector<TreeNode*> childPointerSet;
};

struct Tree {
	TreeNode* root;
};

class FourDirectionGraph {
	Vertex** graph_;
	int height_;
	int width_;

public:
	explicit FourDirectionGraph(Mat m);
	void getMinimumSpanningTreeByKruskalAlgorithm(Tree& t);
	~FourDirectionGraph();
};

#endif FOUR_DIRECTION_GRAPH
