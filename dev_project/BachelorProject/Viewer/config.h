#pragma once
#ifndef	CONFIG_H
#define CONFIG_H
#include <vector>
#include <glew/glew.h>
#include <glm/detail/type_vec3.hpp>

struct ConfigurationData {
	static constexpr const char* windowName = "JawBone Visualizer";
//	static const char* pathToMvmFile;
	static  std::string pathToMvmFile;
//	static const char* pathToMvmRefFile;
	static  std::string pathToMvmRefFile;
	static constexpr const GLchar* vertexPath = "../Viewer/loading.vert";
	static constexpr const GLchar* fragmentPath = "../Viewer/loading.frag";
	static double frequency;
	static bool displayReferenceCube;
	static constexpr const char* uniformModel = "model";
	static constexpr const char* uniformViewPos = "viewPos";
	static constexpr const char* uniformProjection = "projection";
	static constexpr const char* uniformView = "view";
	static constexpr const char* uniformLightAmbient = "light.ambient";
	static constexpr const char* uniformLightDiffuse = "light.diffuse";
	static constexpr const char* uniformLightSpecular = "light.specular";
	static constexpr const char* uniformMaterialShininess = "material.shininess";
	static constexpr const char* uniformLightDirection = "light.direction";

	static constexpr const GLfloat positivePitchBound = 89.0f;
	static constexpr const GLfloat negativePitchBound = -89.0f;
	// Default camera values
	static constexpr const GLfloat YAW = -90.0f;
	static constexpr const GLfloat PITCH = 0.0f;
	static constexpr const GLfloat SPEED = 3.0f;
	static constexpr const GLfloat SENSITIVTY = 0.25f;
	static constexpr const GLfloat ZOOM = 45.0f;

	static glm::vec3 referenceSphere1;
	static glm::vec3 referenceSphere2;
	static glm::vec3 referenceSphere3;
	static glm::vec3 calibrationVertex1;
	static glm::vec3 calibrationVertex2;
	static glm::vec3 calibrationVertex3;

	static std::vector<std::string> stlFiles;
	static GLuint screenWidth;
	static GLuint screenHeight;
};

#endif
