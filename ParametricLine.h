#pragma once
#include <GLFW/glfw3.h>
#include "TransformationComponent.h"

class ParametricLine : public TransformationComponent {
private:
	glm::vec3 start;
	glm::vec3 end;
	float t;
	float lastChangeTime = 0.0f;
	//P(t) = Pstart + (Pend - Pstart) * t
public:
	ParametricLine(glm::vec3 start, glm::vec3 end, float t);
	glm::mat4 apply() override;
};

