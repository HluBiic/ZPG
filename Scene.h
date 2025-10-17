#pragma once
#include "DrawableObject.h"
#include "TransformGroup.h"
#include "Scale.h"
#include "Spin.h"
#include "Translation.h"
#include "Camera.h"
#include "Light.h"

class Scene {
private:
	vector<DrawableObject*> objects;
public:
	Camera* camera;
	vector<Light*> lights;

	Scene();
	void basicScene();
	void symetricalSpheresScene();
	void allLightShadersTestScene();
	void forestScene();
	void galaxy();
	void addObject(DrawableObject* drawObj);

	void draw();

	void moveCam(int key);
};

