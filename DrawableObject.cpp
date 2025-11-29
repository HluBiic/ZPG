#include "DrawableObject.h"

int DrawableObject::IDCounter = 0;

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, TransformationComposite* t) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
	DrawableObject::IDCounter++;
	this->objectId = DrawableObject::IDCounter;
	this->visible = true;
}

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, TransformationComposite* t, Texture* tx) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
	this->texture = tx;
	DrawableObject::IDCounter++;
	this->objectId = DrawableObject::IDCounter;
	this->visible = true;
}

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, TransformationComposite* t, Texture* tx, Material* mat) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
	this->texture = tx;
	this->material = mat;
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

	if (this->material) {
		this->shaderProgram->setUniform("useMaterial", 1);
		this->material->setUniforms(this->shaderProgram, "material");
	} else {
		this->shaderProgram->setUniform("useMaterial", 0);
	}

	if (this->texture) {
		this->shaderProgram->setUniform("useTexture", 1);
		this->texture->bind(0);
		this->shaderProgram->setUniform("textureUnitID", 0);
	} else {
		this->shaderProgram->setUniform("useTexture", 0);
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
