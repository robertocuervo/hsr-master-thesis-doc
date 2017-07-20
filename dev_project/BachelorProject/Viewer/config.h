#pragma once
#ifndef	CONFIG_H
#define CONFIG_H
#include <vector>
#include <glew/glew.h>
#include <glm/detail/type_vec3.hpp>
#include "../common/json_reader.h"

class ConfigurationData {
public:
	static constexpr const char* windowName = "JawBone Visualizer";
	static constexpr const GLchar* vertexPath = "../Viewer/loading.vert";
	static constexpr const GLchar* fragmentPath = "../Viewer/loading.frag";
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
	static JsonReader jsonReader;
	static std::string getPathToMvmFile();
	static std::string getPathToMvmRefFile();
	static double getFrequency();
	static bool getDisplayReferenceCube();

	static glm::vec3 getReferenceSphere1();
	static glm::vec3 getReferenceSphere2();
	static glm::vec3 getReferenceSphere3();
	static glm::vec3 getCalibrationVertex1();
	static glm::vec3 getCalibrationVertex2();
	static glm::vec3 getCalibrationVertex3();

	static std::vector<std::string> getStlFilesPaths();
	static GLuint getScreenWidth();
	static GLuint getScreenHeight();
	static void parseConfigFile(const std::string pathToJsonFile);
};

#endif
