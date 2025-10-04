#include "Rotation.h"

// param angle is in degrees not radiants (conversion is inside of the class in the apply method)
Rotation::Rotation(float angle, glm::vec3 axis) {
	this->angle = angle;
	this->axis = axis;
}

glm::mat4 Rotation::apply() {
	glm::mat4 M = glm::mat4(1.0f); // identity matrix
	M = glm::rotate(M, glm::radians(this->angle), this->axis);
	return M;
}

void Rotation::setAngle(float angle) {
	this->angle = angle;
}

Rotation::~Rotation() {}
