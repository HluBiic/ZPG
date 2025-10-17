#pragma once
#include <glm/ext/vector_float3.hpp>
#include <vector>

#include "IObserver.h"

using namespace std;

class Light{
private:
	//vec3 lightPosition = vec3(0.0, 0.0, 0.0); //Point Light position
	glm::vec3 pointLightPosition;

	vector<IObserver*> observers;

public:
	Light(glm::vec3 position);

	void registerObserver(IObserver* o);
	void unregisterObserver(IObserver* o);
	void notifyAll(); // sends info about light position to all observers
};

