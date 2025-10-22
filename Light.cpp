#include "Light.h"

Light::Light(glm::vec3 position) {
	this->pointLightPosition = position;
}

/*void Light::registerObserver(IObserver* sp) {
	this->observers.push_back(sp);
}

void Light::unregisterObserver(IObserver* sp) {
	this->observers.erase(remove(observers.begin(), observers.end(), sp), observers.end()); //removing by val. of o
}*/

void Light::onChange() {
	notifyObservers();
}

glm::vec3 Light::getLightPos() {
	return this->pointLightPosition;
}

