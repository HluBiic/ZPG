#include "Light.h"

Light::Light(glm::vec3 position, glm::vec4 diffCol, glm::vec4 specCol, float attenConst, float attenLinear, float attenQuadric) {
	this->lightPosition = position;
	this->diffuseColor = diffCol;
	this->specularColor = specCol;
	this->attenConst = attenConst;
	this->attenLinear = attenLinear;
	this->attenQuadric = attenQuadric;
}

void Light::onChange() {
	notifyObservers();
}