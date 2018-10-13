#include "stdafx.h"
#include "Tree.h"

Tree::Tree(): root_(NULL) {
}

Tree::Tree(const pair<int, int> rootPos) {
	TreeNode* tn = new TreeNode();
	tn->pos.first = rootPos.first;
	tn->pos.second = rootPos.second;
	tn->parentNode = NULL;

	root_ = tn;
}

TreeNode* Tree::addChildNode(TreeNode* parent, const pair<int, int> pos, const weight_t w) {
	TreeNode* tn = new TreeNode();
	tn->parentNode = parent;
	tn->parentWeight = w;
	tn->pos = pos;

	parent->vChildNode.push_back(tn);
	parent->vChildWeight.push_back(w);

	return tn;
}

TreeNode* Tree::getRoot() const {
	return root_;
}
