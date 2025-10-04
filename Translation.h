#pragma once
#include "Transformation.h"

class Translation : public Transformation{
private:
	glm::vec3 movementVect;
public:
	Translation(glm::vec3 movementVect);
	glm::mat4 apply() override;
};

