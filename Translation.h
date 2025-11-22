#pragma once
#include "TransformationComponent.h"

class Translation : public TransformationComponent {
private:
	glm::vec3 movementVect;
public:
	Translation(glm::vec3 movementVect);
	glm::mat4 apply() override;
};

