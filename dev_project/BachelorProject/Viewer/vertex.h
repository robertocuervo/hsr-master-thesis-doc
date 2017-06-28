#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <glm/detail/type_vec3.hpp>

/**
 * \brief A vertex is equivalent to a point in a given coordinates system. \n
 * It contains the x, y, z coordinates and the normal coordinates of the point
 */
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
};
#endif
