#ifndef TREE_HPP
#define TREE_HPP

#include <vector>

using namespace std;

typedef int weight_t;

struct TreeNode {
	pair<int, int> pos;
	TreeNode* parentNode = NULL;
	weight_t parentWeight = -1;
	vector<TreeNode*> vChildNode;
	vector<weight_t> vChildWeight;
};

class Tree {
public:
	Tree();
	explicit Tree(pair<int, int> rootPos);
	TreeNode* getRoot() const;
	static TreeNode* addChildNode(TreeNode* parent, pair<int, int> pos, weight_t w);

private:
	TreeNode* root_;
};

#endif TREE_HPP
