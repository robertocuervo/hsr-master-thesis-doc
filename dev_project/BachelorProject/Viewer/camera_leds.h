#pragma once
#ifndef CAMERA_LEDS_H
#define CAMERA_LEDS_H
#include "../common/mvm_parser.h"
#include "vertex.h"
#include "mesh.h"
#include "IDisplayable.h"
#include "UIController.h"

/**
 * \brief This class displays the leds employed by the 3D cameras used to record the jaw movement.\n
 * The leds are grouped in 2 triangles, the first being static and the second displaying the movement of the jaw.
 */
class CameraLeds :public Mesh, public IDisplayable {

public:
	void setUp(const std::string mvmFilePath);
	void render(UIController* uiController) override;
	void update(UIController* uiController) override;

private:
	std::vector<Frame> frames;
	bool isDisplayable{false};
	void getFramesFromMvmFile(const std::string mvmFilePath);
	/**
	 * \brief Extracts the Leds coordinates from the frames to vertex objects.\n
	 *  Only the odd leds (frames) are used until now.
	 */
	void createVertexsForLeds();
	void rotateVertices();
	std::vector<GLuint> getIndicesFromFrames() const;
	glm::vec3 rotateVertexCoordinates(const glm::vec3 originalCoordinates) const;
};

#endif
