#pragma once

#include "targetver.h"

#include <iostream>
#include <cstring>
#include <vector>

#include <opencv2/opencv.hpp>

#include "FourDirectionGraph.h"

using namespace std;
using namespace cv;

#define GRAY_SCALE_IMAGE 0

#define CONES_NAME "cones"
#define CONES_LEFT "dataset/cones_img_0.png"
#define CONES_RIGHT "dataset/cones_img_1.png"
#define CONES_RESULT "result/cones_disp.png"

#define TEDDT_NAME "teddy"
#define TEDDY_LEFT "dataset/teddy_img_0.png"
#define TEDDY_RIGHT "dataset/teddy_img_1.png"
#define TEDDY_RESULT "result/teddy_disp.png"

#define TSUKUBA_NAME "tsukuba"
#define TSUKUBA_LEFT "dataset/tsukuba_img_0.png"
#define TSUKUBA_RIGHT "dataset/tsukuba_img_1.png"
#define TSUKUBA_RESULT "result/tsukuba_disp.png"

#define VENUS_NAME "venus"
#define VENUS_LEFT "dataset/venus_img_0.png"
#define VENUS_RIGHT "dataset/venus_img_1.png"
#define VENUS_RESULT "result/venus_disp.png"

struct TestDataInfo {
	string testName;
	string leftImagePath;
	string rightImagePath;
	string resultPath;

	TestDataInfo(const string testName, const string leftImagePath, const string rightImagePath, const string resultPath) {
		this->testName = testName;
		this->leftImagePath = leftImagePath;
		this->rightImagePath = rightImagePath;
		this->resultPath = resultPath;
	}
};

void initializeTestDataset(vector<TestDataInfo>& dataset);
