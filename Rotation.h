#pragma once
#include <GLFW/glfw3.h>

#include "Transformation.h"

class Rotation : public Transformation {
private:
	float angle;
	glm::vec3 axis;
public:
	Rotation(float angle, glm::vec3 axis);
	glm::mat4 apply() override;
	void setAngle(float angle);
	~Rotation();
};

