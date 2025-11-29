#pragma once
#include "TransformationComponent.h"
#include <GLFW/glfw3.h>

#include <iostream> //only for the testPrint
using namespace std;

class BezierSimple : public TransformationComponent {
private:
	glm::vec3 p0; glm::vec3 p1; glm::vec3 p2; glm::vec3 p3;
	float speed;

	float t = 0.0f;

	glm::mat4 A = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0.0),
		glm::vec4(-3.0, 3.0, 0.0, 0.0),
		glm::vec4(1.0, 0.0, 0.0, 0.0)
	);

	glm::mat4 derivA = glm::mat4(
		glm::vec4(-3.0, 9.0, -9.0, 3.0),
		glm::vec4(6.0, -12.0, 6.0, 0.0),
		glm::vec4(-3.0, 3.0, 0.0, 0.0),
		glm::vec4(0.0, 0.0, 0.0, 0.0)
	);

	glm::mat4x3 B;

	float lastChangeTime = 0.0f;
	bool reverse = false;
public:
	BezierSimple(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float speed);
	glm::mat4 apply() override;
	//ONLY FOR DEBUGING
	void testPrint();
};

