#include "TransformGroup.h"

void TransformGroup::add(Transformation* t) {
	this->children.push_back(t);
}

glm::mat4 TransformGroup::apply() {
	glm::mat4 M = glm::mat4(1.0f);
	for (Transformation* t : this->children) {
		M = t->apply() * M;
	}
	return M;
}
