#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"
#include "TransformGroup.h"
#include "Spin.h"
#include "Texture.h"

class DrawableObject {
protected:
	ShaderProgram* shaderProgram;
	Model* model;
	Transformation* transformation;
	Texture* texture;

	int ID = 0;
public:
	DrawableObject();
	DrawableObject(ShaderProgram* sp, Model* m, Transformation* t);
	DrawableObject(ShaderProgram* sp, Model* m, Transformation* t, Texture* tx);

	void setShader();
	void unsetShader();
	void setModel();
	void setTransformation();

	void draw();

	void resetLightCounter();

	int getID();
};
