#include "Scene.h"

Scene::Scene() {

}

void Scene::addObject(DrawableObject* drawObj) {
	//this->objects.emplace_back(&drawObj);
}

//adds a general object
void Scene::addGenObject() {
	this->objects.emplace_back(DrawableObject());
}

void Scene::draw() {
	for (int i = 0; i < this->objects.size(); i++) {
		this->objects.at(i).draw();
	}
}
