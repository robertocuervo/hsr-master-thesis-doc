#pragma once
#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H
#include <glew/glew.h>
#include "target_frame_structs.h"
#include <glm/gtc/matrix_transform.hpp>

class MatrixCalculator {
public:

	static glm::vec3 MatrixCalculator::calculateDirectionVector(const glm::vec3 pos1, const glm::vec3 pos2) {
		return (pos2 - pos1) / (glm::length(pos2 - pos1));
	}

	static glm::vec3 MatrixCalculator::calculateCentroid(const glm::vec3 positionLed1, const glm::vec3 positionLed2, const glm::vec3 positionLed3) {
		return (positionLed1 + positionLed2 + positionLed3) / GLfloat{3.0f};
	}

	static TransformData MatrixCalculator::calculateTransformData(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3) {
		auto resultTransformData = TransformData{};
		resultTransformData.Centroid = calculateCentroid(position1, position2, position3);
		resultTransformData.DirectionU = calculateDirectionVector(position1, position2);
		resultTransformData.DirectionV = calculateDirectionVector(position1, position3);
		resultTransformData.DirectionK = calculateDirectionVector(-resultTransformData.DirectionV, resultTransformData.DirectionU);
		resultTransformData.DirectionL = calculateDirectionVector(resultTransformData.DirectionV, resultTransformData.DirectionU);
		resultTransformData.DirectionM = glm::cross(resultTransformData.DirectionK, resultTransformData.DirectionL);
		return resultTransformData;
	}

	static glm::mat4 MatrixCalculator::calculateTransformationMatrix(const TransformData origin, const TransformData target) {
		auto temp = glm::outerProduct(target.DirectionK, origin.DirectionK) +
				glm::outerProduct(target.DirectionL, origin.DirectionL) +
				glm::outerProduct(target.DirectionM, origin.DirectionM);
		glm::mat4 result = temp;
		result[3] = glm::vec4(target.Centroid - temp * origin.Centroid, 1.0f);
		return result;
	}
};
#endif
