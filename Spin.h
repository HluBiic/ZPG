#pragma once
#include <GLFW/glfw3.h>

#include "TransformationComponent.h"

class Spin : public TransformationComponent {
private:
	float angle;
	float spinRate; //in degrees per second
	glm::vec3 axis;
public:
	Spin(float spinRate, glm::vec3 axis);
	glm::mat4 apply() override;
	void setAngle(float angle);
};