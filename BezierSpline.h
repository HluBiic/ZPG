#pragma once
#include "TransformationComponent.h"
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

class BezierSpline : public TransformationComponent {
private:
	vector<glm::vec3> points;

	float speed;

	float t = 0.0f;

	glm::mat4 A = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)
	);

	glm::mat4x3 B;

	float lastChangeTime = 0.0f;
	bool reverse = false;

public:
	BezierSpline(vector<glm::vec3> points, float speed);
	glm::mat4 apply() override;
	//ONLY FOR DEBUGING
	void testPrint();
};