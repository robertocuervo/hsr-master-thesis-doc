#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <glew/glew.h>
#include <glm/glm.hpp>
#include "config.h"

/**
 * \brief Defines several possible options for camera movement.\n 
 * Used as abstraction to stay away from window-system specific input methods
 */
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

/**
 * \brief  An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
 */
class Camera {
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;

	GLfloat Zoom;

	/**
	 * \brief Constructor with vectors
	 * \param position 
	 * \param up 
	 * \param yaw 
	 * \param pitch 
	 */
	Camera(const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
	       const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
	       const GLfloat yaw = ConfigurationData().YAW,
	       const GLfloat pitch = ConfigurationData().PITCH);

	/**
	 * \brief Constructor with scalar values
	 * \param posX 
	 * \param posY 
	 * \param posZ 
	 * \param upX 
	 * \param upY 
	 * \param upZ 
	 * \param yaw 
	 * \param pitch 
	 */
	Camera(const GLfloat posX,
	       const GLfloat posY,
	       const GLfloat posZ,
	       const GLfloat upX,
	       const GLfloat upY,
	       const GLfloat upZ,
	       const GLfloat yaw,
	       const GLfloat pitch);

	/**
	 * \brief 
	 * \return The view matrix calculated using Eular Angles and the LookAt Matrix
	 */
	glm::mat4 GetViewMatrix() const;
	/**
	 * \brief Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	 * \param direction 
	 * \param deltaTime 
	 */
	void ProcessKeyboard(const Camera_Movement direction, const GLfloat deltaTime);

	/**
	 * \brief Processes input received from a mouse input system. Expects the offset value in both the x and y direction. 
	 * \param xoffset 
	 * \param yoffset 
	 * \param constrainPitch 
	 */
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, const GLboolean constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(const GLfloat yoffset);

private:
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	/**
	 * \brief Calculates the front vector from the Camera's (updated) Eular Angles
	 */
	void updateCameraVectors();
};
#endif
