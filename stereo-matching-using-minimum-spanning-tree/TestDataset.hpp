#ifndef TEST_DATASET_HPP
#define TEST_DATASET_HPP

#include <string>
#include <vector>

using namespace std;

const std::string cones = "cones";
const string tsukuba = "tsukuba";
const string teddy = "teddy";
const string venus = "venus";

const string conesLeft = "dataset/cones_img_0.png";
const string conesRight = "dataset/cones_img_1.png";
const string conesResult = "result/cones_disp.png";

const string tsukubaLeft = "dataset/tsukuba_img_0.png";
const string tsukubaRight = "dataset/tsukuba_img_1.png";
const string tsukubaResult = "result/tsukuba_disp.png";

const string teddyLeft = "dataset/teddy_img_0.png";
const string teddyRight = "dataset/teddy_img_1.png";
const string teddyResult = "result/teddy_disp.png";

const string venusLeft = "dataset/venus_img_0.png";
const string venusRight = "dataset/venus_img_0.png";
const string venueResult = "result/venus_disp.png";

class TestDataset {
public:
	TestDataset(string testName, string leftImagePath, string rightImagePath, string resultPath);
	string getTestName() const;
	string getLeftImagePath() const;
	string getRightImagePath() const;
	string getResultPath() const;
	static void initializeTestDatasetVector(vector<TestDataset>& v);

private:
	string testName_;
	string leftImagePath_;
	string rightImagePath_;
	string resultPath_;
};

#endif TEST_DATASET_HPP
