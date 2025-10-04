#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Base component of the Composite (abstract base cls)
class Transformation {
private:

public:
	virtual glm::mat4 apply() = 0;
};
