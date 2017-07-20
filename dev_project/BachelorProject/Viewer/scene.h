#pragma once
#ifndef SCENE_H
#define	SCENE_H
#define GLEW_STATIC
#include <glew/glew.h>
#include "Mesh.h"
#include "shader.h"
#include "frame.h"
#include "targetFrame.h"
#include "config.h"
#include "IDisplayable.h"
#include "UIController.h"
#include "cube.h"
#include "camera_leds.h"

class Scene : public IDisplayable {
public:
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center;
	float maxRadius;

	Scene();
	void init();
	void finish() const;
	void render(UIController* uiController) override;
	void update(UIController* uiController) override;

private:
	bool firstMouse{true};
	bool firstCall{true};
	double initTime{-1.0f};
	GLfloat deltaTime{0.0};
	GLfloat lastFrame{0.0};
	ConfigurationData configurationData;
	std::vector<Mesh> meshes;
	std::vector<Frame> frames;
	std::vector<TargetFrame> targetFrames;

	Shader shader;
	Cube cube;
	CameraLeds cameraLeds;
	void updateSceneMinMax(const glm::vec3 minVector, const glm::vec3 maxVector);
	/**
	* \brief Setup and compile shaders
	* \param vertexPath
	* \param fragmentPath
	* \return
	*/
	void setupShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void generateTargetFrames(const std::string pathToMvmFile, const std::string pathToMvmRefFile);
	void loadMeshesFromStlFiles(const std::vector<std::string> stl_files);
	void translateModel(const Shader shader, glm::mat4 transformationMatrix) const;
	void clearColorBuffer(const GLclampf red, const GLclampf green, const GLclampf blue, const GLclampf alpha) const;
	void setLightsProperties() const;
	void setMaterialProperties() const;
	void drawMeshes(const Shader shader, const TargetFrame targetFrame) const;
	void setFrameTime();
	void setLightDirectionlocation() const;
	size_t getFrameIndex(const GLfloat currentTime);
};
#endif
