#include "DrawableObject.h"

float something[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* vertex_shader_uniform =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"uniform mat4 modelMatrix;"
"out vec4 vertexColor;"
"void main () {"
"     gl_Position = modelMatrix * vec4 (vp, 1.0);" //multiply each verice in vertex shader with the transformation matrix
"	  vertexColor = vec4(vc, 1.0);"
"}";

const char* vertex_shader_detail =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec4 vertexColor;" //passing color to frag. shader
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  vertexColor = vec4 (vc, 1.0);" //aplha set to 1.0
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.0, 0.5, 0.5, 1.0);"
"}";

const char* fragment_shader_detail =
"#version 330\n"
"in vec4 vertexColor;" //received from vert. shader
"out vec4 fragColor;"
"void main () {"
"     fragColor = vertexColor;"
"}";



DrawableObject::DrawableObject() {
	this->shaderProgram = new ShaderProgram(vertex_shader_uniform, fragment_shader_detail);
	this->model = new Model(something, size(something), 6);
	this->transformation = nullptr;
	
}

void DrawableObject::setShader() {
	this->shaderProgram->useShaderProgram();
}

void DrawableObject::setModel() {
	this->model->setupRawModel();
}

void DrawableObject::setTransformation() {
	glm::mat4 M = glm::mat4(1.0f);
	float time = (float)glfwGetTime();
	float angle = glm::radians(time * 20.f);
	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	this->shaderProgram->setUniform("modelMatrix", M);
}

void DrawableObject::draw() {
	this->shaderProgram->useShaderProgram();
	this->setTransformation();
	this->model->draw();
}
