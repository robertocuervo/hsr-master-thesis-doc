#include "camera_leds.h"
#include <numeric>
#include "matrix_calculator.h"

void CameraLeds::setUp(const std::string mvmFilePath) {
	this->getFramesFromMvmFile(mvmFilePath);
	this->createVertexsForLeds();
	this->rotateVertices();
	this->indices = getIndicesFromFrames();
	this->setupMesh();
}

void CameraLeds::render(UIController* uiController) {
	if (this->isDisplayable) {
		this->drawMesh();
	}
}

void CameraLeds::update(UIController* uiController) {
	this->isDisplayable = uiController->displayCameraLeds;
}


void CameraLeds::getFramesFromMvmFile(const std::string mvmFilePath) {
	MvmFileManager mvmFileManager{};
	this->frames = mvmFileManager.getFramesFromMvmFile(mvmFilePath);
	MvmFileManager().transformLedCoordinates(this->frames);

}

void CameraLeds::createVertexsForLeds() {
	std::for_each(this->frames.cbegin(), this->frames.cend(), [&](const auto frame) {
	              for (auto i = 0; i < 12; i += 2) {
		              Vertex vertex{};
		              vertex.Position = frame.leds.at(i).ledPosition;
		              vertex.Normal = glm::vec3(1.0f, -1.0f, 1.0f);
		              this->updateMeshMinMax(vertex.Position);
		              this->vertices.push_back(vertex);
	              }
              });
}

void CameraLeds::rotateVertices() {
	std::transform(this->vertices.begin(), this->vertices.end(), this->vertices.begin(), [&](auto vertex) {
	               vertex.Position = this->rotateVertexCoordinates(vertex.Position);
	               return vertex;
               });
}


std::vector<GLuint> CameraLeds::getIndicesFromFrames() const {
	std::vector<GLuint> indices(this->frames.size() * 18 - 1);
	std::iota(indices.begin(), indices.end(), 0);
	return indices;
}

glm::vec3 CameraLeds::rotateVertexCoordinates(const glm::vec3 originalCoordinates) const {
	glm::mat4 rotationMatrix;
	return glm::vec3(rotationMatrix * glm::vec4(originalCoordinates, 1.0f));
}
