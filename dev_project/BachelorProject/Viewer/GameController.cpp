#include "GameController.h"
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include "scene.h"
#include "../common/json_reader.h"

GameController::GameController(): uiController() {}

void GameController::init(const std::string pathToJsonConfig) {
	this->loadConfigurationFromJsonFile(pathToJsonConfig);
	this->initGLFW();
	this->setUpControllers();
	this->initializeGLEW();
	this->defineViewPortDimensions();
	this->setupOpenG_Options();
	this->initalizeDisplayableComponents();
}

void GameController::gameLoop() {
	while (uiController.runLoop) {
		for (auto component : displayableComponents) {
			component->update(&uiController);
			component->render(&uiController);
		}
	}
}

void GameController::finish() const {
	glfwTerminate();
}

void GameController::initGLFW() const {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
}

void GameController::initializeGLEW() const {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("glewInit failed");
	}
}

void GameController::defineViewPortDimensions() const {
	glViewport(0, 0, ConfigurationData().getScreenWidth(), ConfigurationData().getScreenHeight());
}

void GameController::setupOpenG_Options() const {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void GameController::initalizeDisplayableComponents() {
	std::shared_ptr<Scene> scene(new Scene);
	scene->init();
	this->uiController.setCameraPosition(scene->max);
	this->uiController.setSceneCenter(scene->center);
	this->displayableComponents.push_back(std::move(scene));
}

void GameController::setUpControllers() {
	this->uiController.init();
	this->uiController.setCallbackFunctions();
}

void GameController::loadConfigurationFromJsonFile(const std::string pathToJsonConfig) const {
	ConfigurationData().parseConfigFile(pathToJsonConfig);
}
