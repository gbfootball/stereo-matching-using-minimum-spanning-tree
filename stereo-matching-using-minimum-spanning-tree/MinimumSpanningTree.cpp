#include "stdafx.h"
#include "MinimumSpanningTree.hpp"

#include <queue>
#include <map>

void MinimumSpanningTree::addEdge(const FourDirectionGraphEdge e) {
	treeEdgeArray_.push_back(e);
	counter_++;
}

int MinimumSpanningTree::getSize() const {
	return counter_;
}

pair<int, int> MinimumSpanningTree::findMinHeightTreeRootNodePos() {
	vector<FourDirectionGraphEdge> vEdgeTemp;
	map<pair<int, int>, int> mapConnectedNodeNum;
	queue<pair<int, int>> qDeleteNode;

	for (vector<FourDirectionGraphEdge>::iterator iter = treeEdgeArray_.begin(); iter != treeEdgeArray_.end(); ++iter) {
		pair<int, int> sp = iter->getSourcePos();
		pair<int, int> dp = iter->getDestPos();

		if (mapConnectedNodeNum.find(sp) == mapConnectedNodeNum.end()) {
			mapConnectedNodeNum.insert(pair<pair<int, int>, int>(sp, 1));
		} else {
			mapConnectedNodeNum[sp]++;
		}

		if (mapConnectedNodeNum.find(dp) == mapConnectedNodeNum.end()) {
			mapConnectedNodeNum.insert(pair<pair<int, int>, int>(dp, 1));
		} else {
			mapConnectedNodeNum[dp]++;
		}

		vEdgeTemp.push_back(*iter);
	}

	cout << endl;

	while (mapConnectedNodeNum.size() > 2) {
		for (map<pair<int, int>, int>::iterator iter = mapConnectedNodeNum.begin(); iter != mapConnectedNodeNum.end(); ++iter) {
			const pair<int, int> nodePos = iter->first;
			const int numConnectedNode = iter->second;

			if (numConnectedNode == 1) {
				qDeleteNode.push(nodePos);
			}
		}

		while (!qDeleteNode.empty()) {
			const pair<int, int> nodePos = qDeleteNode.front();

			qDeleteNode.pop();
			mapConnectedNodeNum.erase(nodePos);

			vector<FourDirectionGraphEdge>::iterator iter = vEdgeTemp.begin();
			while (iter != vEdgeTemp.end()) {
				const pair<int, int> sp = iter->getSourcePos();
				const pair<int, int> dp = iter->getDestPos();

				/*
				 * If a node need to be deleted, it must be leaf node. Thus, we don't need to opearte for next circulations. 
				 */
				if (sp == nodePos) {
					mapConnectedNodeNum[dp]--;
					vEdgeTemp.erase(iter);
					break;
				}

				if (dp == nodePos) {
					mapConnectedNodeNum[sp]--;
					vEdgeTemp.erase(iter);
					break;
				}

				++iter;
			}
		}
	}

	return mapConnectedNodeNum.begin()->first;
}

vector<FourDirectionGraphEdge> MinimumSpanningTree::getTreeEdgeArray() const {
	return treeEdgeArray_;
}
