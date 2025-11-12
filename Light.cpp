#include "Light.h"

Light::Light(glm::vec3 position, glm::vec4 diffCol, glm::vec4 specCol, float attenConst, float attenLinear, float attenQuadric) {
	this->lightPosition = position;
	this->diffuseColor = diffCol;
	this->specularColor = specCol;
	this->attenConst = attenConst;
	this->attenLinear = attenLinear;
	this->attenQuadric = attenQuadric;
	this->type = LightType::POINT;
}

Light::Light(glm::vec4 diffCol) {
	this->diffuseColor = diffCol;
	this->type = LightType::AMBIENT;
}

Light::Light(glm::vec3 lightDir, glm::vec4 diffCol, glm::vec4 specCol) {
	this->lightDirecton = glm::normalize(lightDir);
	this->diffuseColor = diffCol;
	this->specularColor = specCol;

	this->type = LightType::DIRECTIONAL;
}

Light::Light(glm::vec3 position, glm::vec3 lightDir, glm::vec4 diffCol, glm::vec4 specCol, float cutOff, float attenConst, float attenLinear, float attenQuadric) {
	this->lightPosition = position;
	this->lightDirecton = glm::normalize(lightDir);
	this->diffuseColor = diffCol;
	this->specularColor = specCol;
	this->cutOff = cutOff;
	this->attenConst = attenConst;
	this->attenLinear = attenLinear;
	this->attenQuadric = attenQuadric;

	this->type = LightType::SPOT;
}

void Light::onChange() {
	notifyObservers();
}