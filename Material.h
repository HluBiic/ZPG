#pragma once
#include <glm/glm.hpp>

#include "ShaderProgram.h"

class Material {
private:
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material();
	Material(glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular, float snininess);

	void setUniforms(ShaderProgram* sp, const char* name);
};

