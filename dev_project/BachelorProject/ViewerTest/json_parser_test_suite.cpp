#include "stdafx.h"
#include "json_paser_test_suite.h"
#include "cute_lib/cute.h"
#include "../common/json_reader.h"
#include "../Viewer/config.h"
#include <vector>

void test_not_existing_json_file() {
	JsonReader reader{};
	ASSERT_THROWS(reader.parseJsonFile("foo"), std::invalid_argument);
}

void test_display_reference_cube() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL(false, reader.isReferenceCubeActivated());
}

void test_frequency() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(100, reader.getFrequency(), 0.00);
}

void test_referenceSphere1() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(1.1, reader.getReferenceSphere1().x, 0.01);
	ASSERT_EQUAL_DELTA(-1.1, reader.getReferenceSphere1().y, 0.01);
	ASSERT_EQUAL_DELTA(2.2, reader.getReferenceSphere1().z, 0.02);
}

void test_referenceSphere2() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(5.5, reader.getReferenceSphere2().x, 0.00);
	ASSERT_EQUAL_DELTA(-2.26, reader.getReferenceSphere2().y, 0.01);
	ASSERT_EQUAL_DELTA(6.82, reader.getReferenceSphere2().z, 0.01);
}

void test_referenceSphere3() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(2.59, reader.getReferenceSphere3().x, 0.01);
	ASSERT_EQUAL_DELTA(-0.21, reader.getReferenceSphere3().y, 0.01);
	ASSERT_EQUAL_DELTA(7.69, reader.getReferenceSphere3().z, 0.01);
}

void test_calibrationVertex1() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(-8.96, reader.getCalibrationVertex1().x, 0.01);
	ASSERT_EQUAL_DELTA(-23.84, reader.getCalibrationVertex1().y, 0.01);
	ASSERT_EQUAL_DELTA(3.24, reader.getCalibrationVertex1().z, 0.01);
}

void test_calibrationVertex2() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(8.76, reader.getCalibrationVertex2().x, 0.01);
	ASSERT_EQUAL_DELTA(-33.9, reader.getCalibrationVertex2().y, 0.01);
	ASSERT_EQUAL_DELTA(40.1, reader.getCalibrationVertex2().z, 0.01);
}

void test_calibrationVertex3() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL_DELTA(0.43, reader.getCalibrationVertex3().x, 0.01);
	ASSERT_EQUAL_DELTA(7.04, reader.getCalibrationVertex3().y, 0.01);
	ASSERT_EQUAL_DELTA(5.14, reader.getCalibrationVertex3().z, 0.01);
}

void test_mvmFilePath() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	std::string expected{ "../Viewer/DemoData/mvm_File/foo.mvm" };
	ASSERT_EQUAL(expected, reader.getPathToMvmFile());
}

void test_mvmReferenceFilePath() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	std::string expected{ "../Viewer/DemoData/mvm_File/foo2.mvm" };
	ASSERT_EQUAL(expected, reader.getPathToMvmReferenceFile());
}


void test_stlFilesPaths() {
	std::vector<std::string> stlFiles{
		"../Viewer/DemoData/stl_File/foo1.stl",
		"../Viewer/DemoData/stl_File/foo2.stl",
		"../Viewer/DemoData/stl_File/foo3.stl",
		"../Viewer/DemoData/stl_File/foo4.stl",
		"../Viewer/DemoData/stl_File/foo5.stl",
		"../Viewer/DemoData/stl_File/foo6.stl",
		"../Viewer/DemoData/stl_File/foo7.stl"
	};
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	auto index{ 0 };
	for_each(stlFiles.cbegin(), stlFiles.cend(), [&](const auto expectedFilepath) {
		ASSERT_EQUAL(expectedFilepath, reader.getStlFilePaths().at(index));
		index++;
	});
}

void test_screen_measures() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	ASSERT_EQUAL(192, reader.getScreenWidth());
	ASSERT_EQUAL(108, reader.getScreenHeight());

}

cute::suite make_json_parser_test_suite() {
	cute::suite s{};
	s.push_back(CUTE(test_not_existing_json_file));
	s.push_back(CUTE(test_display_reference_cube));
	s.push_back(CUTE(test_frequency));
	s.push_back(CUTE(test_referenceSphere1));
	s.push_back(CUTE(test_referenceSphere2));
	s.push_back(CUTE(test_referenceSphere3));
	s.push_back(CUTE(test_calibrationVertex1));
	s.push_back(CUTE(test_calibrationVertex2));
	s.push_back(CUTE(test_calibrationVertex3));
	s.push_back(CUTE(test_mvmFilePath));
	s.push_back(CUTE(test_mvmReferenceFilePath));
	s.push_back(CUTE(test_stlFilesPaths));
	s.push_back(CUTE(test_screen_measures));
	return s;
}
