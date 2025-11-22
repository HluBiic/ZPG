#pragma once
#include <GLFW/glfw3.h>

#include "TransformationComponent.h"

class Rotation : public TransformationComponent {
private:
	float angle;
	glm::vec3 axis;
public:
	Rotation(float angle, glm::vec3 axis);
	glm::mat4 apply() override;
	void setAngle(float angle);
	~Rotation();
};

