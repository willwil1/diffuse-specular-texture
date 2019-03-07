#pragma once
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<gl/glew.h>

class camera {
public:
	glm::vec3 Position;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	GLfloat pitch = 0.0f;

	float perspec = 45.0;
	camera(glm::vec3);
	glm::mat4 GetViewMatrix();
	void PrecessMouseMovement(GLfloat xoffset, GLfloat yoffset);
};

camera::camera(glm::vec3 p) {
	this->Position = p;
}

glm::mat4 camera::GetViewMatrix() {
	glm::mat4 view;
	view = glm::lookAt(Position, Position + cameraFront, cameraUp);
	return view;
}

void camera::PrecessMouseMovement(GLfloat xoffset, GLfloat yoffset) {
	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->cameraFront = glm::normalize(front);
}