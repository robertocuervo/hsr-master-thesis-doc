#include "targetFrame.h"
#include <glm/gtc/matrix_transform.inl>
#include "matrixSelector.h"


TargetFrame::TargetFrame(const Frame originFrame, const Frame targetFrame) : target(targetFrame), origin(originFrame) {
	std::vector<TransformData> transformDatas{};
	std::vector<LuminosityData> luminosityDatas{};
	transformDatas.clear();
	luminosityDatas.clear();


	bool baseTransform = true;
	for (int i = 0; i + 4 < originFrame.leds.size(); i += 6) {
		auto originLuminosityData = calculateLuminosityData(originFrame.leds.at(i).luminosities, originFrame.leds.at(i + 2).luminosities, originFrame.leds.at(i + 4).luminosities);
		auto targetLuminosityData = calculateLuminosityData(targetFrame.leds.at(i).luminosities, targetFrame.leds.at(i + 2).luminosities, targetFrame.leds.at(i + 4).luminosities);
		auto originData = calculateTransformData(originFrame.leds.at(i).ledPosition, originFrame.leds.at(i + 2).ledPosition, originFrame.leds.at(i + 4).ledPosition);
		auto targetData = calculateTransformData(targetFrame.leds.at(i).ledPosition, targetFrame.leds.at(i + 2).ledPosition, targetFrame.leds.at(i + 4).ledPosition);

		if (baseTransform) {
			//auto matrix = this->calculateTransformationMatrix(targetData, originData); //useForReferenceMVM
			auto matrix = this->calculateTransformationMatrix(originData, targetData);
			this->baseTransformMatrix = matrix;
			baseTransform = false;
			continue;
		}
		luminosityDatas.push_back(originLuminosityData);
		luminosityDatas.push_back(targetLuminosityData);
		transformDatas.push_back(originData);
		transformDatas.push_back(targetData);
	}
	MatrixSelector selector{StrategyType::Fixed};
	int selectedIndex = selector.execute(transformDatas, luminosityDatas);
	auto matrix = this->calculateTransformationMatrix(transformDatas.at(selectedIndex), transformDatas.at(selectedIndex + 1));
	this->transformMatrix = matrix;
}

glm::vec3 TargetFrame::calculateDirectionVector(const glm::vec3 pos1, const glm::vec3 pos2) const {
	return (pos2 - pos1) / (glm::length(pos2 - pos1));
}

glm::vec3 TargetFrame::calculateCentroid(const glm::vec3 positionLed1, const glm::vec3 positionLed2, const glm::vec3 positionLed3) const {
	return (positionLed1 + positionLed2 + positionLed3) / GLfloat{3.0f};
}

TransformData TargetFrame::calculateTransformData(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3) const {
	auto result = TransformData{};
	result.Centroid = this->calculateCentroid(position1, position2, position3);
	result.DirectionU = this->calculateDirectionVector(position1, position2);
	result.DirectionV = this->calculateDirectionVector(position1, position3);
	result.DirectionK = this->calculateDirectionVector(-result.DirectionV, result.DirectionU);
	result.DirectionL = this->calculateDirectionVector(result.DirectionV, result.DirectionU);
	result.DirectionM = glm::cross(result.DirectionK, result.DirectionL);
	return result;
}

LuminosityData TargetFrame::calculateLuminosityData(glm::vec3 luminosity1, glm::vec3 luminosity2, glm::vec3 luminosity3) const {
	LuminosityData result{};
	result.min = glm::vec3(glm::min(luminosity1.x, glm::min(luminosity2.x, luminosity3.x)),
	                       glm::min(luminosity1.y, glm::min(luminosity2.y, luminosity3.y)),
	                       glm::min(luminosity1.z, glm::min(luminosity2.z, luminosity3.z)));
	result.sum = glm::vec3(luminosity1.x + luminosity2.x + luminosity3.x,
	                       luminosity1.y + luminosity2.y + luminosity3.y,
	                       luminosity1.z + luminosity2.z + luminosity3.z);
	result.average = glm::vec3(result.sum.x / 3,
	                           result.sum.y / 3,
	                           result.sum.z / 3);
	return result;
}

glm::mat4 TargetFrame::calculateTransformationMatrix() {
	auto temp = glm::outerProduct(targetData.DirectionK, originData.DirectionK) +
			glm::outerProduct(targetData.DirectionL, originData.DirectionL) +
			glm::outerProduct(targetData.DirectionM, originData.DirectionM);
	this->transformMatrix = temp;
	glm::mat4 result = temp;

	this->transformMatrix[3] = glm::vec4(targetData.Centroid - temp * originData.Centroid, 1.0f);
	result[3] = glm::vec4(targetData.Centroid - temp * originData.Centroid, 1.0f);
	return result;
}

glm::mat4 TargetFrame::calculateTransformationMatrix(TransformData origin, TransformData target) {
	auto temp = glm::outerProduct(target.DirectionK, origin.DirectionK) +
			glm::outerProduct(target.DirectionL, origin.DirectionL) +
			glm::outerProduct(target.DirectionM, origin.DirectionM);
	this->transformMatrix = temp;
	glm::mat4 result = temp;
	this->transformMatrix[3] = glm::vec4(target.Centroid - temp * origin.Centroid, 1.0f);
	result[3] = glm::vec4(target.Centroid - temp * origin.Centroid, 1.0f);
	return result;
}
