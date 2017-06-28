#include "stl_parser.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <algorithm>
#include <filesystem>


namespace stl{
	GLfloat StlFileManager::parse_float(std::ifstream& inputStream) const {
		char f_buf[sizeof(GLfloat)];
		inputStream.read(f_buf, 4);
		auto fptr = reinterpret_cast<GLfloat*>(f_buf);
		return *fptr;
	}

	void StlFileManager::check_error_bits(const std::ifstream& inputStream) const {
		if (inputStream.fail()) {
			throw std::logic_error{"Fail stream failbit. Error state at reading"};
		}
		if (inputStream.bad()) {
			throw std::logic_error{"Fail stream badbit. Error state at reading"};
		}
	}

	glm::vec3 StlFileManager::parse_point(std::ifstream& inputStream) const {
		auto x = this->parse_float(inputStream);
		auto y = this->parse_float(inputStream);
		auto z = this->parse_float(inputStream);
		return glm::vec3{x, y, z};
	}

	void StlFileManager::string_toLower(std::string& inputLine) const {
		std::transform(inputLine.begin(), inputLine.end(), inputLine.begin(), tolower);
	}

	bool StlFileManager::isBinaryFile(std::ifstream& stl_file) const {
		try {
			const std::string facet{"facet"};
			const std::string normal{"normal"};
			std::string line;
			if (!stl_file.is_open()) {
				throw std::logic_error{"Error while opening file"};
			} else {
				while (std::getline(stl_file, line)) {
					this->string_toLower(line);
					auto foundFacet = line.find(facet);
					auto foundNormal = line.find(normal);
					if ((foundFacet != std::string::npos) || (foundNormal != std::string::npos)) {
						stl_file.close();
						return false;
					}
				}
			}
			return true;
		} catch (std::ifstream::failure e) { //TODO return null object
			stl_file.close();
			std::cerr << "Exception checking if stl file is binary\n";
			throw std::logic_error{"Exception checking if stl file is binary"};
		}
		catch (...) { //TODO return null object
			stl_file.close();
			std::cerr << "Unhandled Exception checking if stl file is binary\n";
			throw std::logic_error{"Unhandled Exception checking if stl file is binary"};
		}
	}

	StlData StlFileManager::getDataFromBinaryStlFile(std::ifstream& stlBinaryFile) const {
		try {
			char header_info[80] = "";
			char n_triangles[4];

			stlBinaryFile.read(header_info, 80);
			stlBinaryFile.read(n_triangles, 4);

			std::string h(header_info);
			StlData data{h};
			auto r = reinterpret_cast<unsigned int*>(n_triangles);
			auto num_triangles = *r;
			for (unsigned int i = 0; i < num_triangles; i++) {
				check_error_bits(stlBinaryFile);
				auto normal = this->parse_point(stlBinaryFile);
				auto v1 = this->parse_point(stlBinaryFile);
				auto v2 = this->parse_point(stlBinaryFile);
				auto v3 = this->parse_point(stlBinaryFile);
				data.triangles.push_back(Triangle(normal, v1, v2, v3));
				char dummy[2];
				stlBinaryFile.read(dummy, 2);
			}
			stlBinaryFile.close();
			return data;
		} catch (std::ifstream::failure e) { //TODO return null object
			stlBinaryFile.close();
			std::cerr << "Exception opening/reading/closing binary stl file\n";
			throw std::logic_error{"Exception opening/reading/closing binary stl file"};
		}
		catch (...) { //TODO return null object
			stlBinaryFile.close();
			std::cerr << "Unhandled Exception opening/reading/closing binary stl file\n";
			throw std::logic_error{"Exception opening/reading/closing binary stl file"};
		}
	}

	StlData StlFileManager::parse_binary_stl(const std::string filePath) const {
		std::ifstream stl_file(filePath, std::ios::in | std::ios::binary);
		this->check_error_bits(stl_file);
		return this->getDataFromBinaryStlFile(stl_file);
	}


	StlData StlFileManager::getDataFromAsciiStlFIle(std::ifstream& stlAsciiFile) const {
		try {
			const std::string facet{"facet"};
			const std::string endsolid{"endsolid"};
			std::string s0, s1;
			GLfloat normalX{0.0f}, normalY{0.0f}, normalZ{0.0f}, vertex1X{0.0f}, vertex1Y{0.0f}, vertex1Z{0.0f}, vertex2X{0.0f}, vertex2Y{0.0f}, vertex2Z{0.0f}, vertex3X{0.0f}, vertex3Y{0.0f}, vertex3Z{0.0f};
			char header_info[80] = "";
			stlAsciiFile.read(header_info, 80);
			StlData data{header_info};
			std::string line;
			while (std::getline(stlAsciiFile, line)) {
				this->check_error_bits(stlAsciiFile);
				stlAsciiFile >> s0; // facet || endsolid
				if (s0 == facet) {
					stlAsciiFile >> s1 >> normalX >> normalY >> normalZ; // normal x y z
					stlAsciiFile >> s0 >> s1; // outer loop
					stlAsciiFile >> s0 >> vertex1X >> vertex1Y >> vertex1Z; // vertex x y z
					stlAsciiFile >> s0 >> vertex2X >> vertex2Y >> vertex2Z; // vertex x y z
					stlAsciiFile >> s0 >> vertex3X >> vertex3Y >> vertex3Z; // vertex x y z
					stlAsciiFile >> s0; // endloop
					stlAsciiFile >> s0; // endfacet
					// Generate a new Triangle with Normal as 3 Vertices
					auto normal = glm::vec3(normalX, normalY, normalZ);
					auto vertex1 = glm::vec3(vertex1X, vertex1Y, vertex1Z);
					auto vertex2 = glm::vec3(vertex2X, vertex2Y, vertex2Z);
					auto vertex3 = glm::vec3(vertex3X, vertex3Y, vertex3Z);
					data.triangles.push_back(Triangle(normal, vertex1, vertex2, vertex3));
				} else if (s0 == endsolid) {
					break;
				}
			}
			stlAsciiFile.close();
			return data;
		} catch (std::ifstream::failure e) {
			stlAsciiFile.close();
			std::cerr << "Exception opening/reading/closing ascii stl file\n";
			throw std::logic_error{"Exception opening/reading/closing ascii stl file"};
		}
		catch (...) {
			stlAsciiFile.close();
			std::cerr << "Unhandled Exception opening/reading/closing ascii stl file\n";
			throw std::logic_error{"Exception opening/reading/closing ascii stl file"};
		}
	}

	StlData StlFileManager::parse_ascii_stl(const std::string filePath) const {
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		this->check_error_bits(in);
		return this->getDataFromAsciiStlFIle(in);
	}

	StlData StlFileManager::parse_stl_file(const std::string filePath) const {
		if (std::experimental::filesystem::exists(filePath)) {
			std::ifstream temp_stream(filePath, std::ios::in | std::ios::binary);
			if (this->isBinaryFile(temp_stream)) {
				return this->parse_binary_stl(filePath);
			} else {
				return this->parse_ascii_stl(filePath);
			}
		} else {
			std::cerr << "The given file " + filePath + " does not exist\n";
			throw std::logic_error{"The given file does not exist"};
		}
	}
}
