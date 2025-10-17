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

glm::mat4 Camera::updateViewMatrix() {
	return glm::lookAt(this->eye, this->eye + this->target, this->up);
}

glm::mat4 Camera::updateProjectionMatrix() {
	return glm::perspective(glm::radians(this->fovyDeg), (float)this->width / (float)this->height, this->zNear, this->zFar);
}

void Camera::registerObserver(IObserver* sp) {
	this->observers.push_back(sp);
}

void Camera::unregisterObserver(IObserver* sp) {
	this->observers.erase(remove(observers.begin(), observers.end(), sp), observers.end()); //removing by val. of sp
}

void Camera::notifyAll() {
	glm::mat4 view = updateViewMatrix();
	glm::mat4 proj = updateProjectionMatrix();
	for (auto o: observers) {
		o->camUpdated(view, proj, this->eye);
	}
}

void Camera::setViewportSize(int w, int h) {
	this->width = w;
	this->height = h;
	notifyAll();
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

	notifyAll();
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
	notifyAll();
}
