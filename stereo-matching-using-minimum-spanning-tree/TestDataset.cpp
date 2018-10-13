#include "stdafx.h"
#include "TestDataset.hpp"

TestDataset::TestDataset(const string testName, const string leftImagePath, const string rightImagePath, const string resultPath) {
	testName_ = testName;
	leftImagePath_ = leftImagePath;
	rightImagePath_ = rightImagePath;
	resultPath_ = resultPath;
}

string TestDataset::getTestName() const {
	return testName_;
}

string TestDataset::getLeftImagePath() const {
	return leftImagePath_;
}

string TestDataset::getRightImagePath() const {
	return rightImagePath_;
}

string TestDataset::getResultPath() const {
	return resultPath_;
}

void TestDataset::initializeTestDatasetVector(vector<TestDataset>& v) {
	v.push_back(TestDataset(cones, conesLeft, conesRight, conesResult));
	v.push_back(TestDataset(teddy, teddyLeft, teddyRight, teddyResult));
	v.push_back(TestDataset(tsukuba, tsukubaLeft, tsukubaRight, teddyResult));
	v.push_back(TestDataset(venus, venusLeft, venusRight, venueResult));
}
