#pragma once
#include "Transformation.h"

class RandTranslateDynamic : public Transformation {
private:
	glm::vec3 startPosition;
	glm::vec3 maxDistance;

	glm::vec3 currPosition;
	glm::vec3 randVelo;

	float maxSpeed = 0.5f;
public:
	RandTranslateDynamic(glm::vec3 startPos, glm::vec3 maxDist);
	glm::mat4 apply() override;
};

