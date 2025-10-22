#pragma once
#include <glm/mat4x4.hpp>

class ObserverSubject;
class IObserver {
public:
	//virtual void lightUpdate(glm::vec3 lightPos) = 0; //previously in ILightObserver;
	//virtual void camUpdated(glm::mat4 view, glm::mat4 proj, glm::vec3 camPos) = 0; //previously in ICamObserver;
	virtual void update(ObserverSubject* s) = 0; //update method needs to be general
};
