#pragma once

#include "DrawableObject.h"

class Scene {
private:
	vector<DrawableObject> objects;
public:
	Scene();
	void addObject(DrawableObject* drawObj);
	void addGenObject();
	void draw();
};

