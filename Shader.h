#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>

using namespace std;

//https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
class Shader {
private:
	GLuint shaderID;
public:
	Shader();
	void createShader(GLenum shaderType, const char* shaderCode);
	void createShaderFromFile(GLenum shaderType, const char* shaderFile);
	void attachShader(GLuint idShaderProgram);
};

