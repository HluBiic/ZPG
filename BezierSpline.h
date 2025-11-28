#pragma once
#include "TransformationComponent.h"
#include <vector>

using namespace std;

//TODO
class BezierSpline : public TransformationComponent {
private:
	vector<glm::vec3> points;
public:
	BezierSpline(vector<glm::vec3> points);
	glm::mat4 apply() override;
};