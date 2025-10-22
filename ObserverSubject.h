#pragma once
#include <vector>

#include "IObserver.h"

using namespace std;

class ObserverSubject {
private:
	vector<IObserver*> observers;

public:
	virtual ~ObserverSubject() = default; //for dynamic_cast
	void registerObserver(IObserver* o);
	void unregisterObserver(IObserver* o);
	void notifyObservers();
};

