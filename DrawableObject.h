#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "TransformationComponent.h"
#include "Rotation.h"
#include "Scale.h"
#include "ParametricLine.h"
#include "RandMovement.h"
#include "Translation.h"
#include "WCustomTransform.h"
#include "TransformationComposite.h"
#include "Spin.h"
#include "Texture.h"
#include <string>

constexpr const char* VERTEX_SHADER = "vertex_shader.glsl";
constexpr const char* CONSTANT_FRAGMENT_SHADER = "constant_fragment_shader.glsl";

class DrawableObject {
protected:
	int objectId;

	static int IDCounter;
public:
	ShaderProgram* shaderProgram;
	Model* model;
	TransformationComposite* transformation;
	Texture* texture;

	bool visible = false;

	DrawableObject();
	DrawableObject(ShaderProgram* sp, Model* m, TransformationComposite* t);
	DrawableObject(ShaderProgram* sp, Model* m, TransformationComposite* t, Texture* tx);

	void setShader();
	void unsetShader();
	void setModel();
	void setTransformation();

	void draw();

	void resetLightCounter();

	int getID();

	string getModelName();
};
