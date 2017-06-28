#include "stdafx.h"
#include "mvn_parser_test_suite.h"
#include "cute_lib/cute.h"
#include "../common/mvm_parser.h"
#include <numeric>
#include <iostream>
#include "../Viewer/frame.h"

enum Coordinates {Xcoordinate,Ycoordinate,Zcoordinate};

std::vector<GLfloat> getAllLuminositiesFromFrame(const Frame frame) {
	std::vector<GLfloat> luminosities{};
	for (auto led : frame.leds) {
		luminosities.push_back(led.luminosities.x);
	};
	for (auto led : frame.leds) {
		luminosities.push_back(led.luminosities.y);
	};
	for (auto led : frame.leds) {
		luminosities.push_back(led.luminosities.z);
	};
	return luminosities;
}


std::vector<GLfloat> getAllCoordinatesFromLed(const std::vector<Frame> frames, const int ledIndex, const Coordinates coordinate) {
	std::vector<GLfloat> coordinatesX{};
	switch (coordinate) {
		case Xcoordinate:
			for (auto frame : frames) {
				auto led = frame.leds.at(ledIndex);
				coordinatesX.push_back(led.ledPosition.x);
			};
			break;
		case Ycoordinate:
			for (auto frame : frames) {
				auto led = frame.leds.at(ledIndex);
				coordinatesX.push_back(led.ledPosition.y);
			};
			break;
		case Zcoordinate:
			for (auto frame : frames) {
				auto led = frame.leds.at(ledIndex);
				coordinatesX.push_back(led.ledPosition.z);
			};
			break;

	}
	return coordinatesX;
}


std::vector<GLfloat> calculateDifferenceBetweenTwoConsecutiveVectorElements(std::vector<GLfloat>& elements) {
	std::adjacent_difference(elements.cbegin(), elements.cend(), elements.begin());
	elements.erase(elements.begin());
	return elements;
}

GLfloat calculateMean(std::vector<GLfloat> elements) {
	auto sum = std::accumulate(elements.cbegin(), elements.cend(), 0.0);
	auto mean = sum / elements.size();
	std::vector<double> diff(elements.size());
	std::transform(elements.begin(), elements.end(), diff.begin(), [mean](double x) { return x - mean; });
	return std::abs(mean);
}

std::vector<GLfloat> calculateMeansFromCoordinatesDifferencesInOddLeds(const std::vector<Frame> frames, Coordinates coordinate) {
	std::vector<GLfloat> means{};
	for (auto i = 0; i < 18; i += 2) {
		auto allCoordinatesYFromOneLed = getAllCoordinatesFromLed(frames, i, coordinate);
		calculateDifferenceBetweenTwoConsecutiveVectorElements(allCoordinatesYFromOneLed);
		auto mean = calculateMean(allCoordinatesYFromOneLed);
		means.push_back(mean);
	}
	return means;
}

void testInverseMappingFunctionWithZero() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(0);
	ASSERT_EQUAL_DELTA(-163.84, result, 0.0001);
}

void testInverseMappingFunctionWithIntegerMax() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(65535);
	ASSERT_EQUAL_DELTA(163.84, result, 0.0001);
}

void testInverseMappingFunctionMiddle() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(32768);
	ASSERT_EQUAL_DELTA(0.0, result, 0.003);
}

void testInverseMappingFunction() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(39875);
	ASSERT_EQUAL_DELTA(35.5359, result, 0.003);
}

void testInverseMappingFunctionWithNegativeOutput() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(28163);
	ASSERT_EQUAL_DELTA(-23.0214461, result, 0.003);
}

void testInverseMappingFunction3() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(35245);
	ASSERT_EQUAL_DELTA(12.38693294, result, 0.003);
}

void testInverseMappingFunction2() {
	MvmFileCamera camera{};
	auto result = camera.getCoordinateInverseMapping(38926);
	ASSERT_EQUAL_DELTA(30.7910904097047, result, 0.003);
}

void test_read_mvm_file_with_size() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	ASSERT_EQUAL(800, frames.size());
}

void test_read_mvm_file_frame1_led1_position() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame = frames.at(0);
	auto led1 = frame.leds.at(0);
	ASSERT_EQUAL_DELTA(35.53587, led1.ledPosition.x, 0.003);
	ASSERT_EQUAL_DELTA(30.79109, led1.ledPosition.y, 0.003);
	ASSERT_EQUAL_DELTA(22.63146, led1.ledPosition.z, 0.003);
}

void test_read_mvm_file_frame1_led15_position() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame = frames.at(0);
	auto led1 = frame.leds.at(14);
	ASSERT_EQUAL_DELTA(-23.0214, led1.ledPosition.x, 0.003);
	ASSERT_EQUAL_DELTA(12.20694, led1.ledPosition.y, 0.003);
	ASSERT_EQUAL_DELTA(14.66183, led1.ledPosition.z, 0.003);
}

void test_read_mvm_file_frame800_led15_position() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame = frames.at(799);
	auto led1 = frame.leds.at(14);
	ASSERT_EQUAL_DELTA(-23.04144518, led1.ledPosition.x, 0.003);
	ASSERT_EQUAL_DELTA(12.38693294, led1.ledPosition.y, 0.003);
	ASSERT_EQUAL_DELTA(14.55183383, led1.ledPosition.z, 0.003);
}


void test_mvm_file1_frame15_all_luminosities() {
	std::vector<GLfloat> expectedFrame1Luminosities{30,21,29,17,29,18,36,2,30,17,38,18,28,19,23,3,21,17,
		46,20,48,3,52,4,62,4,52,3,58,17,40,3,40,4,39,17,27,21,30,17,33,1,39,16,35,16,44,1,21,17,28,1,24,16};
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame15 = frames.at(14);
	auto actualLuminosities = getAllLuminositiesFromFrame(frame15);
	auto index{0};
	std::for_each(actualLuminosities.cbegin(), actualLuminosities.cend(), [&](auto actualLuminosity) {
		              ASSERT_EQUAL(expectedFrame1Luminosities.at(index), actualLuminosity);
		              index++;
	              });
}

void test_mvm_file1_frame800_all_luminosities() {
	std::vector<GLfloat> expectedFrame800Luminosities{29,21,29,2,30,19,35,4,30,18,38,19,28,19,23,18,20,18,46,21,
		48,2,53,4,61,4,52,4,58,4,41,3,40,3,39,2,28,19,30,0,34,0,41,1,37,16,42,1,21,18,28,0,24,15};
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame800 = frames.at(799);
	auto actualLuminosities = getAllLuminositiesFromFrame(frame800);
	auto index{0};
	std::for_each(actualLuminosities.cbegin(), actualLuminosities.cend(), [&](auto actualLuminosity) {
		              ASSERT_EQUAL(expectedFrame800Luminosities.at(index), actualLuminosity);
		              index++;
	              });
}


void test_read_mvm_file_frame1_timeStamp() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame = frames.at(0);
	ASSERT_EQUAL_DELTA(0.0, frame.timeStamp, 0.001);
}

void test_read_mvm_file_frame1_timeStamp2() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame = frames.at(799);
	ASSERT_EQUAL_DELTA(3.995, frame.timeStamp, 0.001);
}

void test_read_mvm_file2_with_size() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	ASSERT_EQUAL(2560, frames.size());
}

void test_read_mvm_file2_frame1_led5_position() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	auto frame = frames.at(0);
	auto led1 = frame.leds.at(4);
	ASSERT_EQUAL_DELTA(21.98649348, led1.ledPosition.x, 0.003);
	ASSERT_EQUAL_DELTA(36.90581048, led1.ledPosition.y, 0.003);
	ASSERT_EQUAL_DELTA(35.8808574, led1.ledPosition.z, 0.003);
}

void test_read_mvm_file2_frame200_led5_position() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	auto frame = frames.at(1999);
	auto led1 = frame.leds.at(4);
	ASSERT_EQUAL_DELTA(21.77650309, led1.ledPosition.x, 0.003);
	ASSERT_EQUAL_DELTA(36.90081071, led1.ledPosition.y, 0.003);
	ASSERT_EQUAL_DELTA(36.15584482, led1.ledPosition.z, 0.003);
}


void test_frame_zero_all_coordinates() {
	std::vector<GLfloat> frameZeroExpectedCoordX{35.53804227f, 132.2795184f, 16.32274907f, 16.31774899f, 20.25280903f, 75.84865736f, 12.30268772f, 12.3076878f,-5.752587778f, 133.0345299f, 5.877589685f, 62.63345571f, -3.787557794f, 133.6495393f, -23.0228513f, 50.9282771f, -12.59769223f, 54.6833344f};
	std::vector<GLfloat> frameZeroExpectedCoordY{30.79296986f, -21.29782498f, 35.97804898f, 35.88304753f, 32.33799344f, -117.6842957f, -0.452506905f, -0.497507591f, 5.157578698f, -22.40784192f, -0.4325066f, -140.0046363f, 8.022622416f, -22.31284047f, 12.20768627f, -156.6098897f, 9.637647059f, -148.5197662f};
	std::vector<GLfloat> frameZeroExpectedCoordZ{22.63284535f,-122.489369f, 17.73777066f, -131.6345086f, 39.45310201f, -107.8191452f, -38.13808194f, -38.08808118f, -34.84803174f, -122.619371f, -16.72775525f, -104.6740972f, 13.8677116f, -123.5443851f, 14.66272374f, 11.65767788f, 34.3280238f, -102.5740652f};
	auto index{0};
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frameZero = frames.at(0);
	std::for_each(frameZero.leds.cbegin(), frameZero.leds.cend(), [&](MvmLed led) {
		              ASSERT_EQUAL_DELTA(frameZeroExpectedCoordX.at(index), led.ledPosition.x, 0.003);
		              ASSERT_EQUAL_DELTA(frameZeroExpectedCoordY.at(index), led.ledPosition.y, 0.003);
		              ASSERT_EQUAL_DELTA(frameZeroExpectedCoordZ.at(index), led.ledPosition.z, 0.003);
		              index++;
	              });
}

void test_frame_one_all_coordinates() {
	std::vector<GLfloat> frameOneExpectedCoordX{35.53804227f, 131.9995142f, 16.33274922f, 74.44363592f, 20.2378088f, 75.83365713f, 12.31268788f, 65.64850172f,-5.747587701f, 58.07838621f, 5.89758999f, 133.9395438f,-3.772557565f, 133.5895384f,-23.01785122f, 51.45828519f,-12.582692f, 54.788336f};
	std::vector<GLfloat> frameOneExpectedCoordY{30.80297002f, -21.11282216f, 35.98804913f, -119.3243207f, 32.38299413f, -117.7092961f,-0.47250721f, -134.4845521f, 5.132578317f, -147.1997461f,-0.477507286f,-24.4578732f, 8.037622644f,-21.73283162f, 12.18268589f, -157.7549071f, 9.632646983f,-148.7047691f};
	std::vector<GLfloat> frameOneExpectedCoordZ{22.63284535f,-122.419368f, 17.7277705f, -107.5591412f, 39.42810163f, 32.27299245f, -38.13808194f, -31.74298436f,-34.85303182f, -103.4090779f,-16.74275547f,-16.19274708f, 13.88771191f,-123.4143832f, 14.67272389f, 11.57267659f, 34.31802365f,-102.7290675f};
	auto index{0};
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frameOne = frames.at(1);
	std::for_each(frameOne.leds.cbegin(), frameOne.leds.cend(), [&](MvmLed led) {
		              ASSERT_EQUAL_DELTA(frameOneExpectedCoordX.at(index), led.ledPosition.x, 0.003);
		              ASSERT_EQUAL_DELTA(frameOneExpectedCoordY.at(index), led.ledPosition.y, 0.003);
		              ASSERT_EQUAL_DELTA(frameOneExpectedCoordZ.at(index), led.ledPosition.z, 0.003);
		              index++;
	              });
}

void test_frame_797_all_coordinates() {
	std::vector<GLfloat> frame797ExpectedCoordX{35.51304189f, 132.4695213f, 16.31774899f, 73.73862516f, 20.23280873f, 75.9236585f, 12.25268696f, 65.3784976f, -5.812588693f, 58.04338567f, 5.85758938f, 62.10344762f, -3.807558099f, 134.1045463f, -23.05285176f, 51.25328206f, -12.60769238f, 55.76335088f};
	std::vector<GLfloat> frame797ExpectedCoordY{30.90297154f,-20.82281773f,36.10305089f,-117.5142931f,32.50299596f,-117.9943005f,-0.382505837f,-133.8695427f,5.257580224f,-147.2497469f,-0.342505226f,-138.7546172f,8.167624628f,-23.44285771f,12.34768841f,-157.0748968f,9.737648585f,-150.7598004f};
	std::vector<GLfloat> frame797ExpectedCoordZ{22.46784283f,-122.6393713f,17.57776822f,-107.6291423f,39.29809964f,32.2829926f,-38.30308446f,-31.8829865f,-34.9830338f,-28.38293309f,-16.87275746f,-13.97271321f,13.73770962f,-124.1143938f,14.53272175f,11.50767559f,34.18802167f,27.40291814f};
	auto index{0};
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto frame797 = frames.at(796);
	std::for_each(frame797.leds.cbegin(), frame797.leds.cend(), [&](MvmLed led) {
		              ASSERT_EQUAL_DELTA(frame797ExpectedCoordX.at(index), led.ledPosition.x, 0.003);
		              ASSERT_EQUAL_DELTA(frame797ExpectedCoordY.at(index), led.ledPosition.y, 0.003);
		              ASSERT_EQUAL_DELTA(frame797ExpectedCoordZ.at(index), led.ledPosition.z, 0.003);
		              index++;
	              });
}

void test_frame_75_file7_all_coordinates() {
	std::vector<GLfloat> frame75ExpectedCoordX{37.24306828f, 132.4945217f, 17.81777188f, 81.05373678f, 21.91283436f, 21.91283436f, 18.21777798f, 70.05856901f, -0.207503166f, 61.6234403f, 10.86766583f, 66.42851362f, 98.47400259f, 114.624249f, 103.024072f, 109.574172f, 76.99867491f, 102.1490587f};
	std::vector<GLfloat> frame75ExpectedCoordY{36.28805371f,-21.24282414f,40.88312383f,163.84f,36.76306096f,36.71806027f,6.782603494f,-127.5244459f,11.44767468f,-139.9896361f,6.272595712f,-134.0495454f,-12.54769146f,-54.14832624f,-13.07269947f,-61.4334374f,-58.35839048f,-12.71269398f};
	std::vector<GLfloat> frame75ExpectedCoordZ{18.99778988f,-122.4543685f,14.26771771f,-156.4798877f,35.88804761f,35.96304875f,-38.0830811f,-106.2541213f,-35.58304295f,-29.09294392f,-17.02275975f,-14.07771481f,-113.3592297f,-90.31387808f,-95.40895583f,-89.06885908f,-89.52386603f,-94.80894667f};
	auto index{0};
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	auto frame75 = frames.at(74);
	std::for_each(frame75.leds.cbegin(), frame75.leds.cend(), [&](MvmLed led) {
		              ASSERT_EQUAL_DELTA(frame75ExpectedCoordX.at(index), led.ledPosition.x, 0.003);
		              ASSERT_EQUAL_DELTA(frame75ExpectedCoordY.at(index), led.ledPosition.y, 0.003);
		              ASSERT_EQUAL_DELTA(frame75ExpectedCoordZ.at(index), led.ledPosition.z, 0.003);
		              index++;
	              });
}

void test_tmjrght1_difference_of_odd_leds_coordinates_X_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	for (auto i = 0; i < 18; i += 2) {
		auto allCoordinatesXFromOneLed = getAllCoordinatesFromLed(frames, i, Xcoordinate);
		calculateDifferenceBetweenTwoConsecutiveVectorElements(allCoordinatesXFromOneLed);
		auto max = std::max_element(allCoordinatesXFromOneLed.cbegin(), allCoordinatesXFromOneLed.cend());
		ASSERT_LESS(std::abs(*max), 0.09);
	}
}


void test_tmjrght1_difference_of_odd_leds_coordinates_Y_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	for (auto i = 0; i < 18; i += 2) {
		auto allcoordinatesYFromOneLed = getAllCoordinatesFromLed(frames, i, Ycoordinate);
		calculateDifferenceBetweenTwoConsecutiveVectorElements(allcoordinatesYFromOneLed);
		auto max = std::max_element(allcoordinatesYFromOneLed.cbegin(), allcoordinatesYFromOneLed.cend());
		ASSERT_LESS(std::abs(*max), 0.2);
	}
}

void test_tmjrght1_difference_of_odd_leds_coordinates_Z_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	for (auto i = 0; i < 18; i += 2) {
		auto allcoordinatesZFromOneLed = getAllCoordinatesFromLed(frames, i, Zcoordinate);
		calculateDifferenceBetweenTwoConsecutiveVectorElements(allcoordinatesZFromOneLed);
		auto max = std::max_element(allcoordinatesZFromOneLed.cbegin(), allcoordinatesZFromOneLed.cend());
		ASSERT_LESS(std::abs(*max), 0.09);
	}
}


void test_tmjright7_difference_of_odd_leds_coordinates_X_are_NOT_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	for (auto i = 0; i < 18; i += 2) {
		auto allcoordinatescX = getAllCoordinatesFromLed(frames, i, Xcoordinate);
		auto differenceCoordinatesX = calculateDifferenceBetweenTwoConsecutiveVectorElements(allcoordinatescX);
		auto max = std::max_element(allcoordinatescX.cbegin(), allcoordinatescX.cend());
		ASSERT_LESS(std::abs(*max), 132);
	}
}

void test_tmjright1_means_of_difference_of_odd_leds_coordinates_X_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto means = calculateMeansFromCoordinatesDifferencesInOddLeds(frames, Xcoordinate);
	calculateDifferenceBetweenTwoConsecutiveVectorElements(means);
	for (auto meanDifference : means) {
		ASSERT_LESS(std::abs(meanDifference), 0.00007);
	}
}

void test_tmjright1_means_of_difference_of_odd_leds_coordinates_Y_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto means = calculateMeansFromCoordinatesDifferencesInOddLeds(frames, Ycoordinate);
	calculateDifferenceBetweenTwoConsecutiveVectorElements(means);
	for (auto meanDifference : means) {
		ASSERT_LESS(std::abs(meanDifference), 0.0002);
	};
}

void test_tmjright1_means_of_difference_of_odd_leds_coordinates_Z_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright1.mvm");
	auto means = calculateMeansFromCoordinatesDifferencesInOddLeds(frames, Zcoordinate);
	calculateDifferenceBetweenTwoConsecutiveVectorElements(means);
	for (auto meanDifference : means) {
		ASSERT_LESS(std::abs(meanDifference), 0.00007);
	}
}


void test_tmjright7_means_of_difference_of_odd_leds_coordinates_X_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	auto means = calculateMeansFromCoordinatesDifferencesInOddLeds(frames, Xcoordinate);
	calculateDifferenceBetweenTwoConsecutiveVectorElements(means);
	for (auto meanDifference : means) {
		ASSERT_LESS(std::abs(meanDifference), 0.03);
	}
}

void test_tmjright7_means_of_difference_of_odd_leds_coordinates_Y_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	auto means = calculateMeansFromCoordinatesDifferencesInOddLeds(frames, Ycoordinate);
	calculateDifferenceBetweenTwoConsecutiveVectorElements(means);
	for (auto meanDifference : means) {
		ASSERT_LESS(std::abs(meanDifference), 0.03);
	}
}

void test_tmjright7_means_of_difference_of_odd_leds_coordinates_Z_are_in_acceptable_range() {
	auto frames = MvmFileManager().getFramesFromMvmFile("data/mvm_files/tmjright7.mvm");
	auto means = calculateMeansFromCoordinatesDifferencesInOddLeds(frames, Zcoordinate);
	calculateDifferenceBetweenTwoConsecutiveVectorElements(means);
	for (auto meanDifference : means) {
		ASSERT_LESS(std::abs(meanDifference), 0.03);
	}
}


cute::suite make_suite_mvm_file_parser_test_suite() {
	cute::suite s{};
	s.push_back(CUTE(testInverseMappingFunctionWithZero));
	s.push_back(CUTE(testInverseMappingFunctionWithIntegerMax));
	s.push_back(CUTE(testInverseMappingFunctionMiddle));
	s.push_back(CUTE(testInverseMappingFunction));
	s.push_back(CUTE(testInverseMappingFunction2));
	s.push_back(CUTE(testInverseMappingFunction3));
	s.push_back(CUTE(testInverseMappingFunctionWithNegativeOutput));
	s.push_back(CUTE(test_read_mvm_file_with_size));
	s.push_back(CUTE(test_read_mvm_file_frame1_led1_position));
	s.push_back(CUTE(test_read_mvm_file_frame800_led15_position));
	s.push_back(CUTE(test_mvm_file1_frame15_all_luminosities));
	s.push_back(CUTE(test_mvm_file1_frame800_all_luminosities));
	s.push_back(CUTE(test_read_mvm_file_frame1_timeStamp));
	s.push_back(CUTE(test_read_mvm_file_frame1_timeStamp2));
	s.push_back(CUTE(test_read_mvm_file2_with_size));
	s.push_back(CUTE(test_read_mvm_file2_frame1_led5_position));
	s.push_back(CUTE(test_read_mvm_file2_frame200_led5_position));
	s.push_back(CUTE(test_frame_zero_all_coordinates));
	s.push_back(CUTE(test_frame_one_all_coordinates));
	s.push_back(CUTE(test_frame_797_all_coordinates));
	s.push_back(CUTE(test_frame_75_file7_all_coordinates));
	s.push_back(CUTE(test_tmjrght1_difference_of_odd_leds_coordinates_X_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjrght1_difference_of_odd_leds_coordinates_Y_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjrght1_difference_of_odd_leds_coordinates_Z_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjright7_difference_of_odd_leds_coordinates_X_are_NOT_in_acceptable_range));
	s.push_back(CUTE(test_tmjright1_means_of_difference_of_odd_leds_coordinates_X_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjright1_means_of_difference_of_odd_leds_coordinates_Y_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjright1_means_of_difference_of_odd_leds_coordinates_Z_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjright7_means_of_difference_of_odd_leds_coordinates_X_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjright7_means_of_difference_of_odd_leds_coordinates_Y_are_in_acceptable_range));
	s.push_back(CUTE(test_tmjright7_means_of_difference_of_odd_leds_coordinates_Z_are_in_acceptable_range));
	return s;
}
