#pragma once
#include <vector>

#include "Transformation.h"

using namespace std;

// Composite: group created from basic transformations
class TransformGroup : public Transformation {
private:
	vector<Transformation*> children;
public:
	void add(Transformation* t);
	glm::mat4 apply() override;
};