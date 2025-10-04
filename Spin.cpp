#include "Spin.h"

Spin::Spin(float spinRate, glm::vec3 axis) {
	this->angle = 0;
	this->spinRate = spinRate;
	this->axis = axis;
}

glm::mat4 Spin::apply() {
	glm::mat4 M = glm::mat4(1.0f); // identity matrix
	float time = (float)glfwGetTime();
	this->angle = time * this->spinRate;
	M = glm::rotate(M, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
	return M;
}

void Spin::setAngle(float angle) {
	this->angle = angle;
}
