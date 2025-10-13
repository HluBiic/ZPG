#pragma once
#include <glm/mat4x4.hpp>

class ICamObserver {
public:
	virtual void camUpdated(glm::mat4 view, glm::mat4 proj) = 0;
};

