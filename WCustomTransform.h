#pragma once
#include "TransformationComponent.h"

class WCustomTransform : public TransformationComponent {
private:
	float w;
public:
	WCustomTransform(float w);
	glm::mat4 apply() override;
};

