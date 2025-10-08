#include "DrawableObject.h"


//simple square for testign purposes with given shaders and given transfomrations
DrawableObject::DrawableObject() {
	this->shaderProgram = new ShaderProgram(vertex_shader_uniform, fragment_shader_detail);
	this->model = new Model(triangle, size(triangle), 6);
	
	glm::mat4 M = glm::mat4(1.0f);

	TransformGroup* tg = new TransformGroup();
	
	tg->add(new Scale(glm::vec3(0.3f)));
	//tg->add(new Rotation(15.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	tg->add(new Spin(180.0f, glm::vec3(0.0f, 0.0f, 1.0f))); // spinning 180 degrees per second
	tg->add(new Translation(glm::vec3(0.0f, -0.5f, 0.0f)));
	
	this->transformation = tg;
}

DrawableObject::DrawableObject(ShaderProgram* sp, Model* m, Transformation* t) {
	this->shaderProgram = sp;
	this->model = m;
	this->transformation = t;
}

void DrawableObject::setShader() {
	this->shaderProgram->useShaderProgram();
}

void DrawableObject::setModel() {
	this->model->draw();
}

void DrawableObject::setTransformation() {
	this->shaderProgram->setUniform(this->transformation->apply()); //sends the final transformation matrix to shader to calculate pos of each vertex
	// volat set uniform na projection, view aj model matrix!!!
	this->shaderProgram->setUniform("projectMatrix", this->transformation->apply());
	this->shaderProgram->setUniform("viewMatrix", this->transformation->apply());
	this->shaderProgram->setUniform("modelMatrix", this->transformation->apply());
}

void DrawableObject::draw() {
	this->setShader();
	this->setTransformation();
	this->setModel();
}
