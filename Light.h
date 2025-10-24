#pragma once
#include <glm/ext/vector_float3.hpp>
#include <vector>

#include "ObserverSubject.h"

using namespace std;

class Light : public ObserverSubject {
private:

public:
	glm::vec3 lightPosition;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;

	//for light attenuation
	float attenConst;
	float attenLinear;
	float attenQuadric;

	Light(glm::vec3 position, glm::vec4 diffCol, glm::vec4 specCol, float attenConst, float attenLinear, float attenQuadric);

	void onChange(); // sends info about light position to all observers
};

