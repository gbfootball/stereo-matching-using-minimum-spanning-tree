#include "stdafx.h"

int main() {
	vector<TestDataInfo> testDataset;
	initializeTestDataset(testDataset);

	Mat leftImage, rightImage;
	Mat disparityResult;

	for (vector<TestDataInfo>::iterator iter = testDataset.begin(); iter != testDataset.end(); ++iter) {
		leftImage = imread(iter->leftImagePath, GRAY_SCALE_IMAGE);
		rightImage = imread(iter->rightImagePath, GRAY_SCALE_IMAGE);

		// TODO: some function used to implement strero mathcing and return a Mat called "disparityResult"

		imwrite(iter->resultPath, disparityResult);
		cout << 1223 << endl;
	}

	waitKey();
	return 0;
}
