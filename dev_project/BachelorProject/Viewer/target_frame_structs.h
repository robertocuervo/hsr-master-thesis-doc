#pragma once
#ifndef TARGET_FRAME_STRUCTS_H
#define TARGET_FRAME_STRUCTS_H
#include <glm/detail/type_vec3.hpp>

struct TransformData {
	glm::vec3 Centroid;
	glm::vec3 DirectionU;
	glm::vec3 DirectionV;
	glm::vec3 DirectionK;
	glm::vec3 DirectionL;
	glm::vec3 DirectionM;
};

struct LuminosityData {
	glm::vec3 sum;
	glm::vec3 average;
	glm::vec3 min;
};

#endif
