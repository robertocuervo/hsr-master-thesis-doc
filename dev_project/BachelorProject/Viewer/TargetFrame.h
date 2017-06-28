#ifndef TARGETFRAME_H
#define TARGETFRAME_H
#pragma once
#include "frame.h"
#include "target_frame_structs.h"

class TargetFrame {
public:
	TransformData originData;
	TransformData targetData;
	glm::mat4 transformMatrix;
	glm::mat4 baseTransformMatrix;

	TargetFrame() = default;
	TargetFrame(const Frame originFrame, const Frame targetFrame);
	glm::vec3 TargetFrame::calculateDirectionVector(const glm::vec3 pos1, const glm::vec3 pos2) const;
	glm::vec3 TargetFrame::calculateCentroid(const glm::vec3 originLed1, const glm::vec3 originLed2, const glm::vec3 originLed3) const;
	TransformData calculateTransformData(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3) const;
	LuminosityData calculateLuminosityData(glm::vec3 luminosity1, glm::vec3 luminosity2, glm::vec3 luminosity3) const;
	glm::mat4 calculateTransformationMatrix();
	glm::mat4 calculateTransformationMatrix(TransformData origin, TransformData target);
private:
	Frame target;
	Frame origin;
};
#endif
