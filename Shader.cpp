#include "Shader.h"

Shader::Shader() {
	this->shaderID = 0;
}

void Shader::createShader(GLenum shaderType, const char* shaderCode) {
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);
}

void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile) {
	ifstream file(shaderFile);
	if (!file.is_open())
	{
		cout << "Unable to open file " << shaderFile << std::endl;
		exit(-1);
	}
	string shaderCode((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	createShader(shaderType, shaderCode.c_str());
}

void Shader::attachShader(GLuint idShaderProgram) {
	glAttachShader(idShaderProgram, shaderID);
}
