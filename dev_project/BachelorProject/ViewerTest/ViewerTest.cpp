// ViewerTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "cute_lib/cute.h"
#include "cute_lib/ide_listener.h"
#include "cute_lib/xml_listener.h"
#include "cute_lib/cute_runner.h"
#include <iostream>

#include "stl_file_parser_test_suite.h"
#include "mvn_parser_test_suite.h"
#include "target_frame_test_suite.h"
#include "json_paser_test_suite.h"

bool runSuite(int argc, char const* argv[]) {
	using namespace std;
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);

	auto runner = cute::makeRunner(lis, argc, argv);
	auto stlFileParserTestSuite{make_suite_stl_file_parser_test_suite()};
	auto mvnFileParserTestSUite{make_suite_mvm_file_parser_test_suite()};
	auto targetFrameTestSuite{make_target_frame_test_suite()};
	auto jsonParserTestSuite{make_json_parser_test_suite()};

	auto success = runner(stlFileParserTestSuite, "STL_FILE_PARSER_TEST_SUITE");
	success = runner(mvnFileParserTestSUite, "MVN_FILE_PARSER_TEST_SUITE") && success;
	success = runner(targetFrameTestSuite, "TARGET_FRAME_TEST_SUITE") && success;
	success = runner(jsonParserTestSuite, "JSON_PARSER_TEST_SUITE") && success;
	std::cin.get();
	return success;
}

int main(int argc, char const* argv[]) {
	return runSuite(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
