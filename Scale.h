#pragma once
#include "TransformationComponent.h"

class Scale : public TransformationComponent {
private:
	glm::vec3 scaleVect;
public:
	Scale(glm::vec3 scaleVect);
	glm::mat4 apply() override;
};

