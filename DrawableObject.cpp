#include "DrawableObject.h"

int DrawableObject::IDCounter = 0;

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, Transformation* t) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
	DrawableObject::IDCounter++;
	this->objectId = DrawableObject::IDCounter;
	this->visible = true;
}

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, Transformation* t, Texture* tx) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
	this->texture = tx;
	DrawableObject::IDCounter++;
	this->objectId = DrawableObject::IDCounter;
	this->visible = true;
}

void DrawableObject::setShader() {
	this->shaderProgram->useShaderProgram();
}

void DrawableObject::unsetShader() {
	this->shaderProgram->unuseShaderProgram();
}

void DrawableObject::setModel() {
	this->model->draw();
}

void DrawableObject::setTransformation() {
	this->shaderProgram->setUniform(this->transformation->apply()); //sends the final transformation matrix to shader to calculate pos of each vertex
	//set uniform for projection and view are directly in cam.
}

void DrawableObject::draw() {
	this->setShader();
	this->setTransformation();

	if (this->texture) {
		this->texture->bind(0);
		this->shaderProgram->setUniform("textureUnitID", 0);
	}

	this->setModel();

	if (this->texture) {
		this->texture->unbind();
	}

	this->unsetShader();
}

void DrawableObject::resetLightCounter() {
	this->shaderProgram->processedLightIndex = 0;
}

int DrawableObject::getID() {
	return this->objectId;
}

string DrawableObject::getModelName() {
	string name = this->model->modelName;
	size_t dot = name.find_last_of('.');
	if (dot != string::npos)
		name = name.substr(0, dot);
	return name;
}
