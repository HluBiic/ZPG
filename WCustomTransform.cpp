#include "WCustomTransform.h"

WCustomTransform::WCustomTransform(float w) {
	this->w = w;
}

glm::mat4 WCustomTransform::apply() {
	glm::mat4 M = glm::mat4(1.0f);
	M[3][3] = w;
	return M;
}
