#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"
#include "TransformGroup.h"
#include "Spin.h"

class DrawableObject {
private:
	ShaderProgram* shaderProgram;
	Model* model;
	Transformation* transformation;
public:
	DrawableObject();
	DrawableObject(ShaderProgram* sp, Model* m, Transformation* t);

	void setShader();
	void setModel();
	void setTransformation();

	void draw();

	void resetLightCounter();
};
