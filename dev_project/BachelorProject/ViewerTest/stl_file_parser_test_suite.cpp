#include "stdafx.h"
#include "stl_file_parser_test_suite.h"
#include "cute_lib/cute.h"
#include <fstream>
#include "../common/stl_parser.h"
#include <iostream>

void test_single_ascii_file_has_one_triangle() {
	stl::StlFileManager manager{};
	auto data = manager.parse_stl_file("data/stl_files/single_triangle.stl");
	ASSERT_EQUAL(1, data.triangles.size());
}

void test_single_ascii_file_coordinates() {
	stl::StlFileManager manager{};
	std::vector<GLfloat> resultCoordinates{};
	std::vector<GLfloat> expectedVertices{13.449456f , 19.596155f , 51.654320f , 14.683020f, 19.940157f, 52.109425f,14.093437f ,19.483467f ,53.230896f};
	auto expectedNormal = glm::vec3{0.331301f, -0.921820f, -0.201214f};
	auto data = manager.parse_stl_file("data/stl_files/single_triangle.stl");

	for (auto coordinate : data.triangles.at(0).vertices) {
		resultCoordinates.push_back(coordinate.x);
		resultCoordinates.push_back(coordinate.y);
		resultCoordinates.push_back(coordinate.z);
	}

	auto index{0};
	std::for_each(resultCoordinates.cbegin(), resultCoordinates.cend(), [&](auto resultVertexCoordinate) {
		              ASSERT_EQUAL_DELTA(expectedVertices.at(index), resultVertexCoordinate,0.0001);
		              index++;
	              });
	ASSERT_EQUAL_DELTA(expectedNormal.x, data.triangles.at(0).normal.x, 0.000001);
	ASSERT_EQUAL_DELTA(expectedNormal.y, data.triangles.at(0).normal.y, 0.000001);
	ASSERT_EQUAL_DELTA(expectedNormal.z, data.triangles.at(0).normal.z, 0.000001);

}

void test_ascii_file_last_triangle_coordinates() {
	stl::StlFileManager manager{};
	std::vector<GLfloat> resultCoordinates{};
	std::vector<GLfloat> expectedVertices{2.062758f,18.049030f, -46.336338f,1.039713f, 17.580128f, -45.427063f,1.560249f,16.486671f, -45.892788f};
	auto expectedNormal = glm::vec3{0.664764f, -0.001725f, 0.747051f};
	auto data = manager.parse_stl_file("data/stl_files/CL.stl");

	for (auto coordinate : data.triangles.at(441).vertices) {
		resultCoordinates.push_back(coordinate.x);
		resultCoordinates.push_back(coordinate.y);
		resultCoordinates.push_back(coordinate.z);
	}

	auto index{0};
	std::for_each(resultCoordinates.cbegin(), resultCoordinates.cend(), [&](auto resultVertexCoordinate) {
		              ASSERT_EQUAL_DELTA(expectedVertices.at(index), resultVertexCoordinate, 0.0001);
		              index++;
	              });
	ASSERT_EQUAL_DELTA(expectedNormal.x, data.triangles.at(441).normal.x, 0.000001);
	ASSERT_EQUAL_DELTA(expectedNormal.y, data.triangles.at(441).normal.y, 0.000001);
	ASSERT_EQUAL_DELTA(expectedNormal.z, data.triangles.at(441).normal.z, 0.000001);

}


void test_ascii_file_first_triangle_coordinates() {
	stl::StlFileManager manager{};
	std::vector<GLfloat> resultCoordinates{};
	std::vector<GLfloat> expectedVertices{7.052784f,6.011117f, -47.192272f,5.761284f,5.746578f, -46.466003f, 6.214034f,5.347749f, -48.134167f};
	auto expectedNormal = glm::vec3{0.353723f, -0.883456f, 0.307222f};
	auto data = manager.parse_stl_file("data/stl_files/CL.stl");

	for (auto coordinate : data.triangles.at(0).vertices) {
		resultCoordinates.push_back(coordinate.x);
		resultCoordinates.push_back(coordinate.y);
		resultCoordinates.push_back(coordinate.z);
	}

	auto index{0};
	std::for_each(resultCoordinates.cbegin(), resultCoordinates.cend(), [&](auto resultVertexCoordinate) {
		              ASSERT_EQUAL_DELTA(expectedVertices.at(index), resultVertexCoordinate, 0.0001);
		              index++;
	              });
	ASSERT_EQUAL_DELTA(expectedNormal.x, data.triangles.at(0).normal.x, 0.000001);
	ASSERT_EQUAL_DELTA(expectedNormal.y, data.triangles.at(0).normal.y, 0.000001);
	ASSERT_EQUAL_DELTA(expectedNormal.z, data.triangles.at(0).normal.z, 0.000001);

}


void test_ascii_file_triangles_quantity() {
	stl::StlFileManager manager{};
	auto data = manager.parse_stl_file("data/stl_files/CL.stl");
	ASSERT_EQUAL(442, data.triangles.size());
}

void test_binary_file_triangles_quantity() {
	stl::StlFileManager manager{};
	auto data = manager.parse_stl_file("data/stl_files/Maxillary2_red_bin_ascii.stl");
	ASSERT_EQUAL(43771, data.triangles.size());
}

void test_is_binary_file_false() {
	std::ifstream in("data/stl_files/Maxillary2_red_bin_ascii.stl", std::ios::in | std::ios::binary);
	stl::StlFileManager manager{};
	ASSERT_EQUAL(false, manager.isBinaryFile(in));
}

void test_is_binary_file_true() {
	std::ifstream in("data/stl_files/Maxillary2_red_bin.stl", std::ios::in | std::ios::binary);
	stl::StlFileManager manager{};
	ASSERT_EQUAL(true, manager.isBinaryFile(in));
}

void test_parse_stl_binary_corrupted_file_with_unhandled_exception() {
	stl::StlFileManager manager{};
	ASSERT_THROWS(manager.parse_stl_file("data/stl_files/Maxillary2_red_binary_wrong.stl"), std::logic_error);
}

void test_file_no_exists_exception() {
	stl::StlFileManager manager{};
	ASSERT_THROWS(manager.parse_stl_file("foo"), std::logic_error);
}


cute::suite make_suite_stl_file_parser_test_suite() {
	cute::suite s{};
	s.push_back(CUTE(test_single_ascii_file_has_one_triangle));
	s.push_back(CUTE(test_single_ascii_file_coordinates));
	s.push_back(CUTE(test_ascii_file_first_triangle_coordinates));
	s.push_back(CUTE(test_ascii_file_last_triangle_coordinates));
	s.push_back(CUTE(test_ascii_file_triangles_quantity));
	s.push_back(CUTE(test_binary_file_triangles_quantity));
	s.push_back(CUTE(test_is_binary_file_false));
	s.push_back(CUTE(test_is_binary_file_true));
	s.push_back(CUTE(test_parse_stl_binary_corrupted_file_with_unhandled_exception));
	s.push_back(CUTE(test_file_no_exists_exception));
	return s;
}
