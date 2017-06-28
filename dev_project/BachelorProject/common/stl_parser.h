#pragma once
#ifndef STL_PARSER_H
#define STL_PARSER_H

#include <vector>
#include <glew/glew.h>
#include <glm/detail/type_vec3.hpp>

namespace stl{
	struct Triangle {
		glm::vec3 normal;
		std::vector<glm::vec3> vertices;

		Triangle(const glm::vec3 normal, const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3) :
			normal(normal), vertices{vertex1, vertex2, vertex3} { }
	};


	class StlData {
	public:
		std::string name;
		std::vector<Triangle> triangles;

		StlData(const std::string name) : name(name) { }
	};

	class StlFileManager {
	public:
		StlData parse_stl_file(const std::string filePath) const;
		bool isBinaryFile(std::ifstream& inputStream) const;
	private:
		StlData parse_binary_stl(const std::string filePath) const;
		StlData parse_ascii_stl(const std::string filePath) const;
		void string_toLower(std::string& inputLine) const;
		glm::vec3 parse_point(std::ifstream& inputStream) const;
		GLfloat parse_float(std::ifstream& inputStreams) const;
		void check_error_bits(const std::ifstream& inputStream) const;
		StlData getDataFromAsciiStlFIle(std::ifstream& in) const;
		StlData getDataFromBinaryStlFile(std::ifstream& stl_file) const;
	};
}

#endif
