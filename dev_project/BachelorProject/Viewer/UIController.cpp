#include "UIController.h"
#include "config.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

template <typename T>
bool check_range(const T value, const T min, const T max) {
	return (value >= min) && (value <= max);
}

UIController::UIController() : displayCube(true), displayCameraLeds(false), runLoop(true), lastX(400), lastY(300) {
	this->keys.resize(1024, false);
	this->camera = Camera{};
}

void UIController::init() {
	this->createGLFW_Window();
}

void UIController::setCallbackFunctions() const {
	auto mouseCallBack = [](GLFWwindow* window, const double xpos, const double ypos) {
		static_cast<UIController*>(glfwGetWindowUserPointer(window))->mouseCallback(window, xpos, ypos);
	};
	glfwSetCursorPosCallback(this->window, mouseCallBack);
	auto keyCallBack = [](GLFWwindow* window, const int key, const int scancode, const int action, const int mode) {
		static_cast<UIController*>(glfwGetWindowUserPointer(window))->keyCallBack(window, key, scancode, action, mode);
	};
	glfwSetKeyCallback(this->window, keyCallBack);
	auto scrollCallBack = [](GLFWwindow* window, const double xoffset, const double yoffset) {
		static_cast<UIController*>(glfwGetWindowUserPointer(window))->scrollCallBack(window, xoffset, yoffset);
	};
	glfwSetScrollCallback(this->window, scrollCallBack);
	auto resizeCallback = [](GLFWwindow* window, const int width, const int height) {
		static_cast<UIController*>(glfwGetWindowUserPointer(window))->resizeCallback(window, width, height);
	};
	glfwSetFramebufferSizeCallback(this->window, resizeCallback);
}

void UIController::doMovement() {
	if (this->keys[GLFW_KEY_W])
		this->camera.ProcessKeyboard(FORWARD, this->deltaTime);
	if (this->keys[GLFW_KEY_S])
		this->camera.ProcessKeyboard(BACKWARD, this->deltaTime);
	if (this->keys[GLFW_KEY_A])
		this->camera.ProcessKeyboard(LEFT, this->deltaTime);
	if (this->keys[GLFW_KEY_D])
		this->camera.ProcessKeyboard(RIGHT, this->deltaTime);
}

void UIController::setDeltaTime(const GLfloat newDeltaTime) {
	this->deltaTime = newDeltaTime;
}

void UIController::setCameraPosition(const glm::vec3 max) {
	this->camera = Camera{glm::vec3(max.x - 45.0f, max.y - 40.0f, max.z + 70.0f)};
}

GLFWwindow* UIController::GetWindow() const {
	return this->window;
}

void UIController::setViewPositionLocation(const Shader shader) const {
	auto viewPosLoc = glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformViewPos);
	glUniform3f(viewPosLoc, this->camera.Position.x, this->camera.Position.y, this->camera.Position.z);
}

void UIController::setProjection(const Shader shader) const {
	auto projection = glm::perspective(this->camera.Zoom, static_cast<float>(ConfigurationData().screenWidth) / static_cast<float>(ConfigurationData().screenHeight), 0.1f, 3000.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformProjection), 1, GL_FALSE, glm::value_ptr(projection));
}

void UIController::setView(const Shader shader) const {
	auto view = this->camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformView), 1, GL_FALSE, glm::value_ptr(view));
}

void UIController::createGLFW_Window() {
	this->window = glfwCreateWindow(ConfigurationData().screenWidth, ConfigurationData().screenHeight, ConfigurationData().windowName, nullptr, nullptr);
	glfwMakeContextCurrent(this->window);
	glfwSetWindowUserPointer(this->window, this);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void UIController::mouseCallback(GLFWwindow* window, const double xpos, const double ypos) {
	if (this->firstMouse) {
		this->lastX = xpos;
		this->lastY = ypos;
		this->firstMouse = false;
	}
	auto xoffset = xpos - this->lastX;
	auto yoffset = this->lastY - ypos;
	this->lastX = xpos;
	this->lastY = ypos;
	this->camera.ProcessMouseMovement(xoffset, yoffset);
}

void UIController::keyCallBack(GLFWwindow* window, const int key, const int scancode, const int action, const int mode) {
	if (check_range(key, 0, 1024)) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			this->runLoop = !this->runLoop; //TODO: remove this dirty hack
		if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
			this->camera.Front = -camera.Front;
		if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
			this->displayCameraLeds = !this->displayCameraLeds;
		if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
			this->camera.Position = glm::vec3(max.x + 50.0f, 0.0f, 0.0f);
		if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
			this->camera.Position = glm::vec3(min.x - 50.0f, 0.0f, 0.0f);
		if (key == GLFW_KEY_F7 && action == GLFW_PRESS)
			this->camera.Position = glm::vec3(0.0f, max.y + 50.0f, 0.0f);
		if (key == GLFW_KEY_F8 && action == GLFW_PRESS)
			this->camera.Position = glm::vec3(0.0f, min.y - 50.0f, 0.0f);
		if (key == GLFW_KEY_F9 && action == GLFW_PRESS)
			this->camera.Position = glm::vec3(0.0f, 0.0f, max.z + 50.0f);
		if (key == GLFW_KEY_F10 && action == GLFW_PRESS)
			this->camera.Position = glm::vec3(0.0f, 0.0f, min.z - 50.0f);
		if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
			this->displayCube = !this->displayCube;

		if (action == GLFW_PRESS)
			this->keys[key] = true;
		else if (action == GLFW_RELEASE)
			this->keys[key] = false;
	}
}

void UIController::scrollCallBack(GLFWwindow* window, const double xoffset, const double yoffset) {
	this->camera.ProcessMouseScroll(yoffset);
}

void UIController::resizeCallback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}
