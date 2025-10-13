#pragma once
#include "DrawableObject.h"
#include "TransformGroup.h"
#include "Scale.h"
#include "Spin.h"
#include "Translation.h"
#include "Camera.h"

class Scene {
private:
	vector<DrawableObject*> objects;
	
public:
	Camera* camera;

	Scene();
	void basicScene();
	void sceneTask6();
	void sceneTask7();
	void cameraScene();
	void addObject(DrawableObject* drawObj);
	void cameraScene2();

	void draw();

	void moveCam(int key);
};

