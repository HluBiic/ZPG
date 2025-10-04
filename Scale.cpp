#include "Scale.h"

Scale::Scale(glm::vec3 scaleVect) {
	this->scaleVect = scaleVect;
}

glm::mat4 Scale::apply() {
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(M, this->scaleVect);
	return M;
}