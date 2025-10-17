#include "Light.h"

Light::Light(glm::vec3 position) {
	this->pointLightPosition = position;
}

void Light::registerObserver(IObserver* sp) {
	this->observers.push_back(sp);
}

void Light::unregisterObserver(IObserver* sp) {
	this->observers.erase(remove(observers.begin(), observers.end(), sp), observers.end()); //removing by val. of o
}

void Light::notifyAll() {
	glm::vec3 pos = this->pointLightPosition;

	for (auto o : observers) {
		o->lightUpdate(pos);
	}
}

