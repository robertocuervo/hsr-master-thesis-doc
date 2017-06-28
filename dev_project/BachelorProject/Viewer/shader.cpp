#include "shader.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>


void Shader::createShaderProgramFromFiles(const GLchar* vertexPath, const GLchar* fragmentPath) {
	auto vertexCode = this->getSourceCodeFromFilePath(vertexPath);
	auto vShaderCode = vertexCode.c_str();
	auto fragmentCode = this->getSourceCodeFromFilePath(fragmentPath);
	auto fShaderCode = fragmentCode.c_str();
	auto vertex = compileShader(vShaderCode, 0);
	auto fragment = compileShader(fShaderCode, 1);
	this->createShaderProgram();
	this->attachShadersToProgram(vertex, fragment);
	this->deleteShaders(vertex, fragment);
}

GLuint Shader::getProgram() const {
	return this->Program;
}

void Shader::Use() const {
	glUseProgram(this->Program);
}

std::string Shader::getSourceCodeFromFilePath(const GLchar* filePath) const {
	std::string sourceCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::badbit);
	if (std::experimental::filesystem::exists(filePath)) {
		try {
			shaderFile.open(filePath);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			sourceCode = shaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			throw std::logic_error{"Shader file not succesfully read"};
		}
	}
	else {
		std::cerr << "The given shader file " + std::string{filePath} + " does not exist\n";
		throw std::logic_error{"The given shader file does not exist"};
	}
	return sourceCode;
}

GLuint Shader::compileShader(const char* vShaderCode, const int index) const {
	const std::vector<int> macros{GL_VERTEX_SHADER , GL_FRAGMENT_SHADER};
	GLint success;
	GLchar infoLog[512];
	auto vertex = glCreateShader(macros[index]);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw std::logic_error{"Vertex shader not succesfully compiled"};
	}
	return vertex;
}

void Shader::createShaderProgram() {
	this->Program = glCreateProgram();
}

void Shader::attachShadersToProgram(const GLuint vertex, const GLuint fragment) const {
	GLint success;
	GLchar infoLog[512];
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		throw std::logic_error{"Program linking failed"};
	}
}

void Shader::deleteShaders(GLuint vertex, GLuint fragment) const {
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
