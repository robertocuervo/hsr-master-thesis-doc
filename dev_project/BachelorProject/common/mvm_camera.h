#pragma once
#ifndef MVM_CAMERA_H
#define MVM_CAMERA_H

#include <glew/glew.h>
#include <vector>
#include <algorithm>

/**
* \brief This struct corresponds to the camera structure in a Mvm file. Used for data import from the mvm files
*/
struct MvmFileCamera {

	uint8_t cameraNumber{};
	uint8_t bitDataLength{};
	uint32_t stepNumber{};
	uint16_t dataMapping{};
	std::vector<uint16_t> leds;
	std::vector<GLfloat> convertedLeds;
	std::vector<uint8_t> luminosities;

	static constexpr double upperOldLevel = 65535.0;
	static constexpr double interval = 327.68;
	static constexpr double bottomNewLevel = -163.84;

	MvmFileCamera() : leds(18), convertedLeds(18), luminosities(18) {}

	/**
	* \brief Translates the given led coordinate from the in Mmv file saved format (integer from 0 ~ 65535)
	* to the new range (-163.84 ~ 163.84 milimeter)
	* \param originalCoordinate
	* \return GLfloat
	*/
	static GLfloat getCoordinateInverseMapping(const uint16_t originalCoordinate) {
		return (originalCoordinate / upperOldLevel) * (interval) + (bottomNewLevel);
	}


	void translateLedCoordinates() {
		std::transform(leds.cbegin(), leds.cend(), convertedLeds.begin(),getCoordinateInverseMapping);
	}
	};
#endif
