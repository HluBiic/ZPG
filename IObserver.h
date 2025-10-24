#pragma once
#include <glm/mat4x4.hpp>

class ObserverSubject;
class IObserver {
public:
	virtual void update(ObserverSubject* s) = 0;
};
