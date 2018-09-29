#include "stdafx.h"

void initializeTestDataset(vector<TestDataInfo>& dataset) {
	dataset.push_back(TestDataInfo(CONES_NAME, CONES_LEFT, CONES_RIGHT, CONES_RESULT));
	dataset.push_back(TestDataInfo(TEDDT_NAME, TEDDY_LEFT, TEDDY_RIGHT, TEDDY_RESULT));
	dataset.push_back(TestDataInfo(TSUKUBA_NAME, TSUKUBA_LEFT, TSUKUBA_RIGHT, TSUKUBA_RESULT));
	dataset.push_back(TestDataInfo(VENUS_NAME, VENUS_LEFT, VENUS_RIGHT, VENUS_RESULT));
}
