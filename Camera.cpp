#include "Camera.h"
#include "ShaderProgram.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

//Default cam constru. with predefined vals.
Camera::Camera() {
	this->eye = glm::vec3(0.5f, 0.0f, 0.0f); //cameraPos in phong shader
	this->target = glm::vec3(-1.0f, 0.0f, 0.0f); //looking towards origin
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->lastX = 400.f;
	this->lastY = 300.f;
	this->alpha = glm::radians(270.0f);
	this->fi = glm::radians(0.0f);
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(this->eye, this->eye + this->target, this->up);
}

glm::mat4 Camera::getProjectionMatrix() {
	this->fovyDeg = 45.0f;
	//first param as radiants otherwise fish eye like camera!!
	return glm::perspective(glm::radians(this->fovyDeg), (float)this->width / (float)this->height, this->zNear, this->zFar);
	//return glm::perspective(this->fovyDeg, (float)this->width / (float)this->height, this->zNear, this->zFar);
}

void Camera::onChange() {
	notifyObservers();
}

void Camera::setViewportSize(int w, int h) {
	this->width = w;
	this->height = h;
	onChange();
}

void Camera::mouseMovement(double xpos, double ypos) {
	if (!this->rotating) {
		return; // only look around when RMB is held
	}

	float xoffset = (float)(xpos - this->lastX);
	float yoffset = (float)(this->lastY - ypos);
	this->lastX = (float)xpos;
	this->lastY = (float)ypos;

	xoffset *= this->sens;
	yoffset *= this->sens;

	this->alpha += xoffset;
	this->fi += yoffset;

	// angle restriction...gimbal lock
	if (this->fi > glm::radians(89.0f)) {
		this->fi = glm::radians(89.0f);
	}
	if (this->fi < glm::radians(-89.0f)) {
		this->fi = glm::radians(-89.0f);
	}

	this->target.x = cos(this->fi) * cos(this->alpha);
	this->target.y = sin(this->fi);
	this->target.z = cos(this->fi) * sin(this->alpha);

	onChange();
}

void Camera::move(int key) {
	switch (key) {
	case GLFW_KEY_W:
		this->eye += this->cameraSpeed * this->target;
		break;
	case GLFW_KEY_S:
		this->eye -= this->cameraSpeed * this->target;
		break;
	case GLFW_KEY_A:
		this->eye -= glm::normalize(glm::cross(this->target, this->up)) * this->cameraSpeed;
		break;
	case GLFW_KEY_D:
		this->eye += glm::normalize(glm::cross(this->target, this->up)) * this->cameraSpeed;
		break;
	}
	onChange();
}
