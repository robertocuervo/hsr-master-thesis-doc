#include "mesh.h"
#include <algorithm>
#include <numeric>
#include "config.h"
#include <glm/detail/func_geometric.inl>
#include <iostream>

void Mesh::setShininess(const Shader shader, const GLfloat value) const {
	glUniform1f(glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformMaterialShininess), value);
}

void Mesh::drawMesh() const {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}


void Mesh::Draw(const Shader shader) const {
	this->setShininess(shader, 16.0f);
	this->drawMesh();
}

/**
 * \brief When required data is ready, sets the vertex buffers and its attribute pointers.
 */
void Mesh::setupMesh() {
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Normal)));
	glBindVertexArray(0);
}


void Mesh::loadMeshDataFromStlFile(const std::string filePath) {
	stl::StlFileManager stlFileManager{};
	//TODO:	handle exceptions from parse_stl_file here or in caller
	auto stlData = stlFileManager.parse_stl_file(filePath);
	this->meshName = filePath;
	this->vertices = this->getVerticesFromStlData(stlData);
	this->indices = this->getIndicesFromStlData(stlData);
}

void Mesh::updateMeshMinMax(const glm::vec3 position) {
	this->min.x = std::min(position.x, min.x);
	this->max.x = std::max(position.x, max.x);
	this->min.y = std::min(position.y, min.y);
	this->max.y = std::max(position.y, max.y);
	this->min.z = std::min(position.z, min.z);
	this->max.z = std::max(position.z, max.z);
}


std::vector<Vertex> Mesh::getVerticesFromStlData(const stl::StlData stlData) {
	std::vector<Vertex> vertices{};
	for (auto triangle : stlData.triangles) {
		for (auto triangleVertex : triangle.vertices) {
			Vertex vertex{};
			glm::vec3 position{triangleVertex.x, triangleVertex.y, triangleVertex.z};
			vertex.Position = position;
			this->updateMeshMinMax(position);
			vertex.Normal = triangle.normal;
			vertices.push_back(vertex);
		}
	}
	this->calculateMeshCentroid();
	return vertices;
}

std::vector<GLuint> Mesh::getIndicesFromStlData(const stl::StlData stlData) const {
	std::vector<GLuint> indices(stlData.triangles.size() * 3 - 1);
	std::iota(indices.begin(), indices.end(), 0);
	return indices;
}

glm::vec3 Mesh::calculateMeshCentroid() const {
	std::cout << this->meshName  <<": Centroid X: " << (this->max.x - this->min.x)/ 2  << " Y:" << (this->max.y - this->min.y)/ 2 << " Z: " << (this->max.z - this->min.z) / 2 << std::endl;
	return glm::vec3((this->max.x - this->min.x)/ 2, (this->max.y - this->min.y)/ 2, (this->max.z - this->min.z) / 2);
}
