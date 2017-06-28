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

private:
	GLfloat lastX;
	GLfloat lastY;
	bool firstMouse{true};
	glm::vec3 min;
	glm::vec3 max;
	std::vector<bool> keys;
	GLfloat deltaTime{0.0};
	GLfloat lastFrame{0.0};
	Camera camera;
	GLFWwindow* window;

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
};
