#pragma once
#include "DrawableObject.h"
#include "TransformGroup.h"
#include "Scale.h"
#include "Spin.h"
#include "Translation.h"

class Scene {
private:
	vector<DrawableObject*> objects;
public:
	Scene();
	void basicScene();
	void sceneTask6();
	void sceneTask7();
	void cameraScene();
	void addObject(DrawableObject* drawObj);
	void draw();
};

