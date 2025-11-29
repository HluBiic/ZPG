#include "Material.h"

Material::Material() {
	this->ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	this->diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	this->specular = glm::vec3(0.3f, 0.3f, 0.3f);
	this->shininess = 32.0f;
}

Material::Material(glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular, float shininess) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

void Material::setUniforms(ShaderProgram* sp, const char* name) {
	string ambient = string(name) + ".ambient";
	string diffuse = string(name) + ".diffuse";
	string specular = string(name) + ".specular";
	string shininess = string(name) + ".shininess";

	sp->setUniform(ambient.c_str(), this->ambient);
	sp->setUniform(diffuse.c_str(), this->diffuse);
	sp->setUniform(specular.c_str(), this->specular);
	sp->setUniform(specular.c_str(), this->specular);
}