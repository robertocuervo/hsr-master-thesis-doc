#include "stdafx.h"
#include "json_paser_test_suite.h"
#include "cute_lib/cute.h"
#include "../common/json_reader.h"
#include "../Viewer/config.h"
#include <vector>

void test_not_existing_json_file() {
	JsonReader reader{};
	ASSERT_THROWS(reader.parseJsonFile("foo") , std::invalid_argument);
}

void test_display_reference_cube() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT(true, ConfigurationData().displayReferenceCube);
}

void test_frequency() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(100, ConfigurationData().frequency, 0.00);
}

void test_referenceSphere1() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(1.1, ConfigurationData().referenceSphere1.x, 0.01);
	ASSERT_EQUAL_DELTA(-1.1, ConfigurationData().referenceSphere1.y, 0.01);
	ASSERT_EQUAL_DELTA(2.2, ConfigurationData().referenceSphere1.z, 0.02);
}

void test_referenceSphere2() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(5.5, ConfigurationData().referenceSphere2.x, 0.00);
	ASSERT_EQUAL_DELTA(-2.26, ConfigurationData().referenceSphere2.y, 0.01);
	ASSERT_EQUAL_DELTA(6.82, ConfigurationData().referenceSphere2.z, 0.01);
}

void test_referenceSphere3() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(2.59, ConfigurationData().referenceSphere3.x, 0.01);
	ASSERT_EQUAL_DELTA(-0.21, ConfigurationData().referenceSphere3.y, 0.01);
	ASSERT_EQUAL_DELTA(7.69, ConfigurationData().referenceSphere3.z, 0.01);
}

void test_calibrationVertex1() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(-8.96, ConfigurationData().calibrationVertex1.x, 0.01);
	ASSERT_EQUAL_DELTA(-23.84, ConfigurationData().calibrationVertex1.y, 0.01);
	ASSERT_EQUAL_DELTA(3.24, ConfigurationData().calibrationVertex1.z, 0.01);
}

void test_calibrationVertex2() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(8.76, ConfigurationData().calibrationVertex2.x, 0.01);
	ASSERT_EQUAL_DELTA(-33.9, ConfigurationData().calibrationVertex2.y, 0.01);
	ASSERT_EQUAL_DELTA(40.1, ConfigurationData().calibrationVertex2.z, 0.01);
}

void test_calibrationVertex3() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL_DELTA(0.43, ConfigurationData().calibrationVertex3.x, 0.01);
	ASSERT_EQUAL_DELTA(7.04, ConfigurationData().calibrationVertex3.y, 0.01);
	ASSERT_EQUAL_DELTA(5.14, ConfigurationData().calibrationVertex3.z, 0.01);
}

void test_mvmFilePath() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT(true, std::strcmp("../Viewer/DemoData/mvm_File/foo.mvm", ConfigurationData().pathToMvmFile));
}

void test_mvmReferenceFilePath() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT(true, std::strcmp("../Viewer/DemoData/mvm_File/foo2.mvm", ConfigurationData().pathToMvmRefFile));
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
	reader.setUpConfigurationData();
	auto index{0};
	for_each(stlFiles.cbegin(), stlFiles.cend(), [&] (const auto expectedFilepath) {
	         ASSERT_EQUAL(expectedFilepath, ConfigurationData().stlFiles.at(index));
	         index++;
         });
}

void test_screen_measures() {
	JsonReader reader{};
	reader.parseJsonFile("data/testConfigCustom.json");
	reader.setUpConfigurationData();
	ASSERT_EQUAL(192, ConfigurationData().screenWidth);
	ASSERT_EQUAL(108, ConfigurationData().screenHeight);

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
