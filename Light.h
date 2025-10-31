#pragma once
#include <glm/ext/vector_float3.hpp>
#include <vector>

#include "ObserverSubject.h"

using namespace std;

enum LightType {
	POINT = 0,
	AMBIENT = 1,
	DIRECTIONAL = 2,
	SPOT = 3
};

class Light : public ObserverSubject {
private:

public:
	glm::vec3 lightPosition = glm::vec3(0.0); //point
	glm::vec4 diffuseColor = glm::vec4(0.0); //point
	glm::vec4 specularColor = glm::vec4(0.0); //point
	glm::vec3 lightDirecton = glm::vec4(0.0); //directional light, spotlihgh

	float cutOff = 0.0f; //beta..angle where light is 1
	float outerCutOff = 0.0f; //alpha..angle where light fades to 0

	//for light attenuation
	float attenConst = 0.0f; //point
	float attenLinear = 0.0f; //point
	float attenQuadric = 0.0f; //point

	int type = LightType::POINT; //default point light

	bool flashlightEnabled = true; //toggle on/off with F


	//point light constructor
	Light(glm::vec3 position, glm::vec4 diffCol, glm::vec4 specCol, float attenConst, float attenLinear, float attenQuadric);

	//ambient light constuctor
	Light(glm::vec4 diffCol);

	//directional light construcot
	Light(glm::vec3 lightDir, glm::vec4 diffCol, glm::vec4 specCol);

	//spotlight constructor
	Light(glm::vec3 position, glm::vec3 lightDir, glm::vec4 diffCol, glm::vec4 specCol, float innerCutOff, float outterCutOff, float attenConst, float attenLinear, float attenQuadric);

	void onChange(); // sends info about light position to all observers
};

