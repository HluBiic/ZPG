#pragma once
#include <GLFW/glfw3.h>
#include "TransformationComponent.h"

using namespace glm;

class RandMovement : public TransformationComponent {
private:
	float speed;
	vec3 min;
	vec3 max;
	vec3 position;
	vec3 direction;
	float lastChangeTime = 0.0f;
public:
	RandMovement(float speed, glm::vec3 min, glm::vec3 max);
	mat4 apply() override;
	void randDir();
};

