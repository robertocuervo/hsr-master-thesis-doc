#include "scene.h"
#include <iostream>
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include "../common/mvm_parser.h"
#include "matrix_calculator.h"
#include <GLFW/glfw3.h>

template <typename T>
bool check_range(const T value, const T min, const T max) {
	return (value >= min) && (value <= max);
}


Frame calculateReferenceFrame(std::vector<Frame> const referenceFrames) {
	std::vector<glm::vec3> sumPositions{18};
	glm::vec3 sumPosition{0.0f};
	std::for_each(referenceFrames.cbegin(), referenceFrames.cend(), [&](const auto frame) {
	              for (auto i = 0; i < 18; i++) {
		              sumPositions.at(i).x += frame.leds.at(i).ledPosition.x;
		              sumPositions.at(i).y += frame.leds.at(i).ledPosition.y;
		              sumPositions.at(i).z += frame.leds.at(i).ledPosition.z;
	              }
              });
	auto referenceFrame = referenceFrames.at(0);
	for (auto i = 0; i < 18; i++) {
		referenceFrame.leds.at(i).ledPosition.x = sumPositions.at(i).x / referenceFrames.size();
		referenceFrame.leds.at(i).ledPosition.y = sumPositions.at(i).y / referenceFrames.size();
		referenceFrame.leds.at(i).ledPosition.z = sumPositions.at(i).z / referenceFrames.size();
	}
	return referenceFrame;
}

//void Scene::generateTargetFrames(const char* pathToMvmFile, const char* pathToMvmRefFile) {
void Scene::generateTargetFrames(const std::string pathToMvmFile, const std::string pathToMvmRefFile) {
	auto referenceFrames = MvmFileManager().getFramesFromMvmFile(pathToMvmRefFile);
	this->frames = MvmFileManager().getFramesFromMvmFile(pathToMvmFile);
	MvmFileManager().transformLedCoordinates(this->frames);
	//auto firstFrame = calculateReferenceFrame(referenceFrames); //useForReferenceMVM
	auto firstFrame = frames.at(0);

	auto originData = MatrixCalculator().calculateTransformData(this->configurationData.calibrationVertex1, this->configurationData.calibrationVertex2, this->configurationData.calibrationVertex3);
	auto anatomyData = MatrixCalculator().calculateTransformData(this->configurationData.referenceSphere1, this->configurationData.referenceSphere2, this->configurationData.referenceSphere3);
	auto transformMatrixOriginToAnatomy = MatrixCalculator().calculateTransformationMatrix(originData, anatomyData);
	std::for_each(firstFrame.leds.begin(), firstFrame.leds.end(), [&](MvmLed& led) {
	              led.ledPosition = glm::vec3(transformMatrixOriginToAnatomy * glm::vec4(led.ledPosition, 1.0f));
              });
	frames.erase(frames.begin());
	std::for_each(frames.begin(), frames.end(), [&](auto frame) {
	              std::for_each(frame.leds.begin(), frame.leds.end(), [&](auto& led) {
	                            led.ledPosition = glm::vec3(transformMatrixOriginToAnatomy * glm::vec4(led.ledPosition, 1.0f));
                            });

	              this->targetFrames.push_back(TargetFrame(firstFrame, frame));
              });
	this->firstCall = true;
}

void Scene::init() {
	this->setupShader(this->configurationData.vertexPath, this->configurationData.fragmentPath);
	this->loadMeshesFromStlFiles(ConfigurationData().stlFiles);
	this->generateTargetFrames(ConfigurationData().pathToMvmFile, ConfigurationData().pathToMvmRefFile);
	this->cube.setUp();
	this->cameraLeds.setUp(ConfigurationData().pathToMvmFile);
}


double lastTime = glfwGetTime();
int nbFrames = 0;

void calculateFPS() {
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		std::cout << "ms/frame\n" << 1000.0 / double(nbFrames);
		std::cout << "FPS\n" << 1 / (1000.0 / double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}
}

void Scene::updateSceneMinMax(const glm::vec3 minVector, const glm::vec3 maxVector) {
	//TODO: update this in update method inherited from IDisplayablle in UIcontroller
	this->min.x = std::min(minVector.x, min.x);
	this->max.x = std::max(maxVector.x, max.x);
	this->min.y = std::min(minVector.y, min.y);
	this->max.y = std::max(maxVector.y, max.y);
	this->min.z = std::min(minVector.z, min.z);
	this->max.z = std::max(maxVector.z, max.z);
	this->center = glm::vec3(min.x + (glm::distance(min.x, max.x) / 2), min.y + (glm::distance(min.y, max.y) / 2), min.z + (glm::distance(min.z, max.z) / 2));
	auto maxRadX = glm::max(glm::distance(this->center.x, min.x), glm::distance(this->center.x, max.x));
	auto maxRadY = glm::max(glm::distance(this->center.y, min.y), glm::distance(this->center.y, max.y));
	auto maxRadZ = glm::max(glm::distance(this->center.z, min.z), glm::distance(this->center.z, max.z));
	this->maxRadius = glm::length(glm::max(maxRadX, glm::max(maxRadY, maxRadZ)));
}

void Scene::loadMeshesFromStlFiles(const std::vector<std::string> stlFiles) {
	//TODO handle possible file I/O exceptions, maybe send them to gui?
	for_each(stlFiles.cbegin(), stlFiles.cend(), [&](const auto filePath) {
	         Mesh mesh{};
	         mesh.loadMeshDataFromStlFile(filePath);
	         mesh.setupMesh();
	         this->updateSceneMinMax(mesh.min, mesh.max);
	         if (filePath.find(std::string("Mandibular")) != std::string::npos ||
		         filePath.find(std::string("CL")) != std::string::npos ||
		         filePath.find(std::string("CR")) != std::string::npos)
		         mesh.stationary = false;
	         this->meshes.push_back(mesh);
         });
}


Scene::Scene(): maxRadius(0.0) {
	this->configurationData = ConfigurationData{};
	this->cube = Cube{};
	this->cameraLeds = CameraLeds{};
}


void Scene::setupShader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	this->shader = Shader();
	this->shader.createShaderProgramFromFiles(vertexPath, fragmentPath);
}

void Scene::translateModel(const Shader shader, glm::mat4 transformationMatrix) const {
	glm::mat4 model = transformationMatrix;
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), ConfigurationData().uniformModel), 1, GL_FALSE, glm::value_ptr(model));
}

void Scene::clearColorBuffer(const GLclampf red, const GLclampf green, const GLclampf blue, const GLclampf alpha) const {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::setLightsProperties() const {
	glUniform3f(glGetUniformLocation(this->shader.getProgram(), ConfigurationData().uniformLightAmbient), GLfloat{0.2f}, GLfloat{0.2f}, GLfloat{0.2f});
	glUniform3f(glGetUniformLocation(this->shader.getProgram(), ConfigurationData().uniformLightDiffuse), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(this->shader.getProgram(), ConfigurationData().uniformLightSpecular), 1.0f, 1.0f, 1.0f);
}

void Scene::setMaterialProperties() const {
	glUniform1f(glGetUniformLocation(this->shader.getProgram(), ConfigurationData().uniformMaterialShininess), 32.0f);
}

void Scene::drawMeshes(const Shader shader, const TargetFrame targetFrame) const {
	std::for_each(this->meshes.cbegin(), this->meshes.cend(), [&](const Mesh mesh) {
	              glm::mat4 normMatrix;
	              if (mesh.stationary) {
		              //this->translateModel(shader, targetFrame.baseTransformMatrix); //useForReferenceMVM
		              this->translateModel(shader, normMatrix);
	              }
	              else {
		              //this->translateModel(shader, targetFrame.baseTransformMatrix * targetFrame.transformMatrix); //useForReferenceMVM
		              this->translateModel(shader, glm::inverse(targetFrame.baseTransformMatrix) * targetFrame.transformMatrix);
	              }
	              mesh.Draw(shader);
              });
}


void Scene::setFrameTime() {
	GLfloat currentFrame = glfwGetTime();
	this->deltaTime = currentFrame - this->lastFrame;
	this->lastFrame = currentFrame;
}

void Scene::setLightDirectionlocation() const {
	auto lightDirLoc = glGetUniformLocation(this->shader.getProgram(), ConfigurationData().uniformLightDirection);
	glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
}

void Scene::finish() const {
	glfwTerminate();
}


size_t Scene::getFrameIndex(const GLfloat currentTime) {
	if (this->firstCall) {
		this->firstCall = false;
		initTime = this->lastFrame;
	}
	else {
		if (this->initTime == -1.0f)
			return 0;
	}
	auto length = this->frames.size();
	auto maxDuration = length / ConfigurationData().frequency;;
	auto currentPercentage = (currentTime - initTime) / maxDuration;
	size_t index = currentPercentage * length;
	if (index >= length - 1) {
		this->firstCall = true;
		return length - 1;
	}
	return index;
}

void Scene::update(UIController* uiController) {
	this->setFrameTime();
	uiController->setDeltaTime(this->deltaTime);
	this->clearColorBuffer(0.05f, 0.05f, 0.05f, 1.0f);
	this->setLightDirectionlocation();
	uiController->setViewPositionLocation(this->shader);
	this->setLightsProperties();
	this->setMaterialProperties();
	uiController->setProjection(this->shader);
	uiController->setView(this->shader);
	this->cube.update(uiController);
	this->cameraLeds.update(uiController);
}

void Scene::render(UIController* uiController) {
	calculateFPS();
	auto frameIndex = this->getFrameIndex(this->lastFrame);
	glfwPollEvents();
	uiController->doMovement();
	this->shader.Use();
	this->drawMeshes(this->shader, targetFrames[frameIndex]);
	this->cube.render(uiController);
	this->cameraLeds.render(uiController);
	glfwSwapBuffers(uiController->GetWindow());
}
