#pragma once
#ifndef	MVM_LED_H
#define MVM_LED_H
#include <glm/glm.hpp>
#include <glew/glew.h>

/**
* \brief Corresponds to a MvmLed in a Mvm file. Contains the x, y, z coordinates
* and to each coordinate corresponding luminosity level.\n
* LED 4,5,6 are attached to the mandible - therefore they move.\n
* LED 1,2,3 are attached to the skull - therefore they are quasi static.
*/
struct MvmLed {
	glm::vec3 ledPosition;
	glm::vec3 luminosities;

	void initPositions(const GLfloat x, const GLfloat y, const GLfloat z) {
		this->ledPosition = glm::vec3(x, y, z);
	}

	void initLuminosities(const GLfloat x, const GLfloat y, const GLfloat z) {
		this->luminosities = glm::vec3(x, y, z);
	}
};


#endif
