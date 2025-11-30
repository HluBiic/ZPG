#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>

using namespace std;

class Shader {
private:
	GLuint shaderID;
public:
	Shader();
	void createShader(GLenum shaderType, const char* shaderCode);
	void createShaderFromFile(GLenum shaderType, const char* shaderFile);
	void attachShader(GLuint idShaderProgram);
};

