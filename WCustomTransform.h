#pragma once
#include "Transformation.h"

class WCustomTransform : public Transformation {
private:
	float w;
public:
	WCustomTransform(float w);
	glm::mat4 apply() override;
};

