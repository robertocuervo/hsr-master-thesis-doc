#include "UIController.h"
#include "config.h"
#include <iostream>
#include <glm/glm.hpp>
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

void UIController::setSceneCenter(glm::vec3 center)
{
	this->sceneCenter = center;
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
	auto mouseButtonCallback = [](GLFWwindow* window, const int button, const int action, const int mods) {
		static_cast<UIController*>(glfwGetWindowUserPointer(window))->mouseButtonCallback(window, button, action, mods);
	};
	glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
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

glm::mat4 UIController::getViewMatrix() const {
	return this->ViewMatrix;
}

glm::mat4 UIController::getProjectionMatrix() const {
	return this->ProjectionMatrix;
}


void UIController::setViewPositionLocation(const Shader shader) const {
	auto viewPosLoc = glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformViewPos);
	glUniform3f(viewPosLoc, this->camera.Position.x, this->camera.Position.y, this->camera.Position.z);
}

void UIController::setProjection(const Shader shader) const {
	auto projection = glm::perspective(this->camera.Zoom, static_cast<float>(ConfigurationData().getScreenWidth()) / static_cast<float>(ConfigurationData().getScreenHeight()), 0.1f, glm::distance(this->camera.Position, this->sceneCenter) + glm::sqrt(glm::pow(174.0f, 2) * 2));
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformProjection), 1, GL_FALSE, glm::value_ptr(projection));
}

void UIController::setView(const Shader shader) const {
	auto view = this->camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformView), 1, GL_FALSE, glm::value_ptr(view));
}

void UIController::createGLFW_Window() {
	this->window = glfwCreateWindow(ConfigurationData().getScreenWidth(), ConfigurationData().getScreenHeight(), ConfigurationData().windowName, nullptr, nullptr);
	glfwMakeContextCurrent(this->window);
	glfwSetWindowUserPointer(this->window, this);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited movement
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
			this->runLoop = !this->runLoop; 
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
	auto oldCamPos = camera.Position;
	auto d = oldCamPos + glm::dot(sceneCenter - oldCamPos, camera.Front) * camera.Front;
	if (glm::distance(oldCamPos, d) < 1)
	{
		std::cout << "oldcampos on centroid plane" << std::endl;
		if (yoffset <= 0)
		{
			this->scrollRotations -= 1;
			d += camera.Front * 10.0f;
			auto newCamPos = d + std::pow(scrollFactor, -scrollRotations) * (oldCamPos - d);
			auto zoomFactor = std::pow(scrollFactor, -scrollRotations);
			auto newFoV = initialFoV * zoomFactor;
			std::cout << "zoomFactor:" << zoomFactor << std::endl;
			std::cout << "newFoV:" << newFoV << std::endl;
			std::cout << "scrollRotations: " << scrollRotations << "; d:" << d.x << ";" << d.y << ";" << d.z << std::endl;
			std::cout << "oldCamPos:" << oldCamPos.x << ";" << oldCamPos.y << ";" << oldCamPos.z << std::endl;
			std::cout << "newCamPos:" << newCamPos.x << ";" << newCamPos.y << ";" << newCamPos.z << std::endl;

			camera.Position = newCamPos;
			this->camera.ProcessMouseScroll(yoffset);
		}
		
	}
	else
	{
		if (yoffset > 0)
			this->scrollRotations += 1;
		else
			this->scrollRotations -= 1;
		auto newCamPos = d + std::pow(scrollFactor, -scrollRotations) * (oldCamPos - d);
		auto zoomFactor = std::pow(scrollFactor, -scrollRotations);
		auto newFoV = initialFoV * zoomFactor;
		std::cout << "zoomFactor:" << zoomFactor << std::endl;
		std::cout << "newFoV:" << newFoV << std::endl;
		std::cout << "scrollRotations: " << scrollRotations << "; d:" << d.x << ";" << d.y << ";" << d.z << std::endl;
		std::cout << "oldCamPos:" << oldCamPos.x << ";" << oldCamPos.y << ";" << oldCamPos.z << std::endl;
		std::cout << "newCamPos:" << newCamPos.x << ";" << newCamPos.y << ";" << newCamPos.z << std::endl;

		camera.Position = newCamPos;
		this->camera.ProcessMouseScroll(yoffset);
	}
}

void UIController::resizeCallback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

glm::vec3 UIController::GetWorldCoordinates(const double xPosButtonPressed, const double yPosButtonPressed, const GLfloat depth) {
	auto projectionMatrix = glm::perspective(this->camera.Zoom, static_cast<float>(ConfigurationData().getScreenWidth()) / static_cast<float>(ConfigurationData().getScreenHeight()), 0.1f, glm::distance(this->camera.Position, this->sceneCenter) + glm::sqrt(glm::pow(174.0f, 2) * 2));
	auto viewMatrix = this->camera.GetViewMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	auto viewportVec = glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]);
	auto worldCoords = glm::unProject(glm::vec3(xPosButtonPressed, viewport[3] - yPosButtonPressed, depth), viewMatrix, projectionMatrix, viewportVec);
	std::cout << "worldcoords: (" << worldCoords.x << ", " << worldCoords.y << ", " << worldCoords.z << ");" << "\n";
	return worldCoords;
}

void UIController::mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
	double xPosButtonPressed{0.0}, yPosButtonPressed{0.0}, xPosButtonReleased{0.0}, yPosButtonReleased{0.0}, xOffSet, yOffset;
	glm::vec3 clickStartPos, clickEndPos, camStartPos, camEndPos, d;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { //&& action == GLFW_REPEAT 
		glfwGetCursorPos(this->window, &xPosButtonPressed, &yPosButtonPressed);
		GLfloat depth;
		glReadPixels(xPosButtonPressed, yPosButtonPressed, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		std::cout << "mouse left pressed with coordinates: " << xPosButtonPressed << " : " << yPosButtonPressed << ":" << depth << "\n";
		clickStartPos = this->GetWorldCoordinates(xPosButtonPressed, yPosButtonPressed, depth);
		camStartPos = camera.Position;
		auto clickRayDirection = glm::normalize(clickStartPos - camStartPos);
		auto clickRayPoint = clickStartPos;
		d = camStartPos + glm::dot(sceneCenter - camStartPos, camera.Front) * camera.Front;
		
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwGetCursorPos(this->window, &xPosButtonReleased, &yPosButtonReleased);
		GLfloat depth;
		glReadPixels(xPosButtonPressed, yPosButtonPressed, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		std::cout << "mouse left released with coordinates: " << xPosButtonReleased << " : " << yPosButtonReleased << ":" << depth << "\n";
		clickEndPos = this->GetWorldCoordinates(xPosButtonPressed, yPosButtonPressed, depth);
		camEndPos = clickEndPos + camStartPos - clickStartPos;
		std::cout << "dotproductStartClick:" << glm::dot(camera.Front, (camStartPos - clickStartPos)) << std::endl;
		std::cout << "dotproductEndClick:" << glm::dot(camera.Front, (camEndPos - clickEndPos)) << std::endl;				
		std::cout << "camStartPos:" << camStartPos.x << ";" << camStartPos.y << ";" << camStartPos.z << std::endl;
		std::cout << "camEndPos:" << camEndPos.x << ";" << camEndPos.y << ";" << camEndPos.z << std::endl;
		
		auto clickRayDirection = glm::normalize(clickEndPos - camEndPos);
		auto clickRayPoint = clickEndPos;
		auto tanPhi = 2.0f * ((clickEndPos.x - clickStartPos.x) / static_cast<float>(ConfigurationData().getScreenWidth()) - 0.5f) * glm::tan(camera.Zoom);
		auto tanPhi2 = 2.0f * ((clickEndPos.x - camera.Position.x) / static_cast<float>(ConfigurationData().getScreenWidth()) - 0.5f) * glm::tan(camera.Zoom);
		std::cout << "tanPhi: " << tanPhi << ";" << std::endl;
		std::cout << "tanPhi2: " << tanPhi2 << ";" << std::endl;
		std::cout << "tanPhi arctan: " << std::atan(tanPhi) << ";" << std::endl;
		std::cout << "tanPhi2 arctan: " << std::atan(tanPhi2) << ";" << std::endl;
	}
}
