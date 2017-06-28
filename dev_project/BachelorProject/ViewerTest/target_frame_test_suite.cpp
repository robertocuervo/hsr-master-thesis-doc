#include "stdafx.h"
#include "target_frame_test_suite.h"
#include "cute_lib/cute.h"
#include "../Viewer/scene.h"
#include "../Viewer/targetFrame.h"
#include "../Viewer/target_frame_structs.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

void targetFrame_calculateDirectionVector_test() {
	TargetFrame targetFrame{};
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(2.0f, 4.0f, 5.0f);
	auto resultVector = targetFrame.calculateDirectionVector(a, b);
	ASSERT_EQUAL_DELTA(0.3370, resultVector.x, 0.004);
	ASSERT_EQUAL_DELTA(0.6741, resultVector.y, 0.014);
	ASSERT_EQUAL_DELTA(0.6741, resultVector.z, 0.014);
}

void targetFrame_calculateCentroid_test() {
	TargetFrame targetFrame{};
	glm::vec3 a(1.0f, 3.0f, 3.0f);
	glm::vec3 b(2.0f, 4.0f, 5.0f);
	glm::vec3 c(3.0f, 2.0f, 4.0f);
	auto resultVector = targetFrame.calculateCentroid(a, b, c);
	ASSERT_EQUAL_DELTA(2.0, resultVector.x, 0.001);
	ASSERT_EQUAL_DELTA(3.0, resultVector.y, 0.001);
	ASSERT_EQUAL_DELTA(4.0, resultVector.z, 0.001);
}

void test_apply_matrix() {
	TargetFrame targetFrame{};
	targetFrame.targetData.Centroid = glm::vec3(3.0f, 1.0f, 2.0f); //s'
	targetFrame.targetData.DirectionK = glm::vec3(1.0f, 2.0f, 3.0f);//k'
	targetFrame.targetData.DirectionL = glm::vec3(3.0f, 4.0f, 5.0f);//l'
	targetFrame.targetData.DirectionM = glm::vec3(1.0f, 4.0f, 3.0f);//m'
	targetFrame.originData.DirectionK = glm::vec3(2.0f, 4.0f, 5.0f);//k
	targetFrame.originData.DirectionL = glm::vec3(2.0f, 3.0f, 5.0f);//l
	targetFrame.originData.DirectionM = glm::vec3(2.0f, 7.0f, 3.0f);//m
	targetFrame.originData.Centroid = glm::vec3(2.0f, 4.0f, 3.0f);//s
	glm::vec4 x(5.0f, 3.0f, 2.0f, 0.0f);
	auto result = x * targetFrame.calculateTransformationMatrix();
	ASSERT_EQUAL_DELTA(-10.0, result.x, 0.001);
	ASSERT_EQUAL_DELTA(-29.0, result.y, 0.001);
	ASSERT_EQUAL_DELTA(-29.0, result.z, 0.001);
}

void test_targetFrameCall() {
	TargetFrame targetFrame{};
	glm::vec3 a(1.0f, 3.0f, 3.0f);
	glm::vec3 b(2.0f, 4.0f, 5.0f);
	glm::vec3 c(3.0f, 2.0f, 4.0f);
	MvmLed e{};
	e.ledPosition = a;
	MvmLed f{};
	f.ledPosition = b;
	MvmLed g{};
	g.ledPosition = c;

	glm::mat4 transform;
	transform = glm::rotate(transform, 2.0f, glm::vec3(0.2f, -1.3f, 0.3f));
	transform = glm::translate(transform, glm::vec3(2.0f, 3.2f, 4.1f));
	MvmLed h{};
	h.ledPosition = transform * glm::vec4(a, 1.0f);
	MvmLed i{};
	i.ledPosition = transform * glm::vec4(b, 1.0f);
	MvmLed j{};
	j.ledPosition = transform * glm::vec4(c, 1.0f);
	targetFrame.originData = targetFrame.calculateTransformData(e.ledPosition, f.ledPosition, g.ledPosition);
	targetFrame.targetData = targetFrame.calculateTransformData(e.ledPosition, f.ledPosition, g.ledPosition);
	glm::mat4 res = targetFrame.calculateTransformationMatrix();
	res = res - transform;
	for (int u = 0; u < 4; u++) std::cout << res[u][0] << " " << res[u][1] << " " << res[u][2] << " " << res[u][3] << " " << std::endl;
	std::cout << std::endl;

}

cute::suite make_target_frame_test_suite() {
	cute::suite s{};
	s.push_back(CUTE(targetFrame_calculateDirectionVector_test));
	s.push_back(CUTE(targetFrame_calculateCentroid_test));
	s.push_back(CUTE(test_apply_matrix));
	s.push_back(CUTE(test_targetFrameCall));
	return s;
}
