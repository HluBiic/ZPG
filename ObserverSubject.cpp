#include "ObserverSubject.h"

void ObserverSubject::registerObserver(IObserver* o) {
	this->observers.push_back(o);
}

void ObserverSubject::unregisterObserver(IObserver* o) {
	this->observers.erase(remove(observers.begin(), observers.end(), o), observers.end()); //removing by val. of sp
}

void ObserverSubject::notifyObservers() {
	for (auto* o : observers) {
		o->update(this); // pass pointer to self
	}
}
