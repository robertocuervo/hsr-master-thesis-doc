#pragma once
#include <vector>
#include <memory>
#include "UIController.h"
#include "IDisplayable.h"

class GameController {
public:

	GameController();

	void init(const std::string pathToJsonConfig);
	void gameLoop();
	void finish() const;

private:

	UIController uiController;
	std::vector<std::shared_ptr<IDisplayable>> displayableComponents;

	void initGLFW() const;
	/**
	* \brief Initialize GLEW to setup the OpenGL Function pointers
	*/
	void initializeGLEW() const;
	/**
	* \brief Define the viewport dimensions
	*/
	void defineViewPortDimensions() const;
	void setupOpenG_Options() const;
	void initalizeDisplayableComponents();
	void setUpControllers();
	void loadConfigurationFromJsonFile(const std::string pathToJsonConfig) const;
};
