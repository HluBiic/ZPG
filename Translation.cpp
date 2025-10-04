#include "Translation.h"

Translation::Translation(glm::vec3 movementVect) {
	this->movementVect = movementVect;
}

glm::mat4 Translation::apply() {
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, this->movementVect);
	return M;
}