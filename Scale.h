#pragma once
#include "Transformation.h"

class Scale : public Transformation {
private:
	glm::vec3 scaleVect;
public:
	Scale(glm::vec3 scaleVect);
	glm::mat4 apply() override;
};

