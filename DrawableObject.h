#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

class DrawableObject {
private:
	ShaderProgram* shaderProgram;
	Model* model;
	Transformation* transformation;



public:
	DrawableObject();

	void setShader();
	void setModel();
	void setTransformation();

	void draw();

};

//Drawable object agregaciu nie kompoziciu pozor...pozor na statnice aj 
/*nastavuje sa shader, model, transformacia, draw a color*/
//transfromacia moze byt aj agregacia aj kompozicia



//class Model
//Triangle dedi z model a bude akoby vseobecny triangle
//object dedi z model a bude importovat napriklad zo suboru



// drawable object pri volani draw nastavi shader, model, transformacie



// Renderer vezme scenu s kamerou, modelmy atd a vykresli
