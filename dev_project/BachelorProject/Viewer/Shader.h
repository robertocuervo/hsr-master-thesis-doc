#ifndef SHADER_H
#define SHADER_H
#include <glew/glew.h>
#include <vector>

class Shader {
public:
	Shader() = default;
	void createShaderProgramFromFiles(const GLchar* vertexPath, const GLchar* fragmentPath);
	GLuint getProgram() const;

	/**
	* \brief Uses current shader
	*/
	void Use() const;

private:
	GLuint Program;

	std::string getSourceCodeFromFilePath(const GLchar* filePath) const;
	/**
	* \brief Compiles a vertex or fragment shader with the given code and an OpenGL Macro, the last defining the shader type
	* \param vShaderCode Code obtained from shader file
	* \param index of an array containing the OpenGL Macros, like GL_VERTEX_SHADER
	* \return Gluint compiled shader
	*/
	GLuint compileShader(const char* vShaderCode, const int index) const;
	void createShaderProgram();
	void attachShadersToProgram(const GLuint vertex, const GLuint fragment) const;

	/**
	* \brief Delete the shaders as they're linked into our program now and no longer necessery
	* \param vertex
	* \param fragment
	*/
	void deleteShaders(GLuint vertex, GLuint fragment) const;
};


#endif
