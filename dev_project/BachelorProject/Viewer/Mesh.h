#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "shader.h"
#include "../common/stl_parser.h"
#include "vertex.h"

class Mesh {
public:
	glm::vec3 min{0.0f, 0.0f, 0.0f};
	glm::vec3 max{0.0f, 0.0f, 0.0f};
	bool stationary{true};

	Mesh() = default;

	/**
	* \brief Render the mesh
	* \param shader
	*/
	void Draw(const Shader shader) const;

	/**
	* \brief Initializes all the buffer objects/arrays
	*/
	void setupMesh();
	void loadMeshDataFromStlFile(const std::string filePath);

protected:
	GLuint VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	/**
	* \brief Set each mesh's shininess property to a default value
	* \param shader
	* \param value
	*/
	void setShininess(const Shader shader, const GLfloat value) const;
	void drawMesh() const;
	void updateMeshMinMax(const glm::vec3 vector);
	std::vector<Vertex> getVerticesFromStlData(const stl::StlData stlData);
	std::vector<GLuint> getIndicesFromStlData(const stl::StlData stlData) const;
};
#endif
