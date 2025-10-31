#include "DrawableObject.h"

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, Transformation* t) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
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
	this->setModel();
	this->unsetShader();
}

void DrawableObject::resetLightCounter() {
	this->shaderProgram->processedLightIndex = 0;
}
