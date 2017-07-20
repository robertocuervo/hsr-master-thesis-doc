#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3 position,
               const glm::vec3 up,
               const GLfloat yaw,
               const GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
	this->MovementSpeed = ConfigurationData().SPEED;
	this->MouseSensitivity = ConfigurationData().SENSITIVTY;
	this->Zoom = ConfigurationData().ZOOM;
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera(const GLfloat posX,
               const GLfloat posY,
               const GLfloat posZ,
               const GLfloat upX,
               const GLfloat upY,
               const GLfloat upZ,
               const GLfloat yaw,
               const GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
	this->MovementSpeed = ConfigurationData().SPEED;
	this->MouseSensitivity = ConfigurationData().SENSITIVTY;
	this->Zoom = ConfigurationData().ZOOM;
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::ProcessKeyboard(const Camera_Movement direction, const GLfloat deltaTime) {
	auto velocity = this->MovementSpeed * deltaTime * 5;
	if (direction == FORWARD)
		this->Position += this->Front * velocity;
	if (direction == BACKWARD)
		this->Position -= this->Front * velocity;
	if (direction == LEFT)
		this->Position -= this->Right * velocity;
	if (direction == RIGHT)
		this->Position += this->Right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, const GLboolean constrainPitch) {
	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch) {
		if (this->Pitch > ConfigurationData().positivePitchBound)
			this->Pitch = ConfigurationData().positivePitchBound;
		if (this->Pitch < ConfigurationData().negativePitchBound)
			this->Pitch = ConfigurationData().negativePitchBound;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(const GLfloat yoffset) {
	/*NON-ZOOM-Version
	 *if (yoffset > 0)
		this->Position += this->Front * 10.0f;
	else
		this->Position -= this->Front * 10.0f;*/

	this->updateCameraVectors();
}

void Camera::updateCameraVectors() {
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}
