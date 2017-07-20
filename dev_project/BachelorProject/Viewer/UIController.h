#pragma once
#include <vector>
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <glm/detail/type_vec3.hpp>
#include "camera.h"
#include "shader.h"


class UIController {
public:
	bool displayCube;
	bool displayCameraLeds;
	bool runLoop;

	UIController();
	void init();
	void setSceneCenter(glm::vec3 center);
	void setCallbackFunctions() const;

	/**
	* \brief Moves/alters the camera positions based on user input
	*/
	void doMovement();
	void setDeltaTime(const GLfloat time);
	void setCameraPosition(const glm::vec3 max);
	void setViewPositionLocation(const Shader shader) const;
	void setProjection(const Shader shader) const;
	void setView(const Shader shader) const;
	GLFWwindow* GetWindow() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

private:
	GLfloat lastX;
	GLfloat lastY;
	bool firstMouse{true};
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 sceneCenter;
	std::vector<bool> keys;
	GLfloat deltaTime{0.0};
	GLfloat lastFrame{0.0};
	Camera camera;

	GLFWwindow* window;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;
	float scrollRotations = 0.0f;
	float scrollFactor = 1.1f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;


	void createGLFW_Window();
	void mouseCallback(GLFWwindow* window, const double xpos, const double ypos);
	/**
	* \brief Is called whenever a key is pressed / released via GLFW
	* \param window
	* \param key
	* \param scancode
	* \param action
	* \param mode
	*/
	void keyCallBack(GLFWwindow* window, const int key, const int scancode, const int action, const int mode);
	void scrollCallBack(GLFWwindow* window, const double xoffset, const double yoffset);
	void resizeCallback(GLFWwindow* window, const int width, const int height);
	glm::vec3 GetWorldCoordinates(const double xPosButtonPressed, const double yPosButtonPressed, const GLfloat depth);
	void mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods);
};
