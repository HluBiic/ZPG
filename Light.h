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
	glm::vec3 lightPosition = glm::vec3(0.0);
	glm::vec4 ambientColor = glm::vec4(0.0);
	glm::vec4 diffuseColor = glm::vec4(0.0);
	glm::vec4 specularColor = glm::vec4(0.0);
	glm::vec3 lightDirecton = glm::vec4(0.0);
	
	float cutOff = 0.0f;
	//float innerCutOff = 0.0f;...moved directlry into shader

	//for light attenuation
	float attenConst = 0.0f;
	float attenLinear = 0.0f;
	float attenQuadric = 0.0f;

	int type = LightType::POINT; //default point light

	int flashlightEnabled = 1; //toggle on/off with F...1 ON...0 OFF


	//point light constructor
	Light(glm::vec3 position, glm::vec4 diffCol, glm::vec4 specCol, float attenConst, float attenLinear, float attenQuadric);

	//ambient light constuctor
	Light(glm::vec4 ambientCol);

	//directional light construcot
	Light(glm::vec3 lightDir, glm::vec4 diffCol, glm::vec4 specCol);

	//spotlight constructor
	Light(glm::vec3 position, glm::vec3 lightDir, glm::vec4 diffCol, glm::vec4 specCol, float cutOff, float attenConst, float attenLinear, float attenQuadric);

	void onChange(); // sends info about light position to all observers
};

