#include "Shader.h"

Shader::Shader() {
	this->shaderID = 0;
}

void Shader::createShader(GLenum shaderType, const char* shaderCode) {
	// Creates an empty shader
	shaderID = glCreateShader(shaderType);
	// Sets the source code of the shader.
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	// Compiles the shader source code
	glCompileShader(shaderID);
}

void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile) {
	//Loading the contents of a file into a variable
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
	//Attaches the shader to the shaderProgram
	glAttachShader(idShaderProgram, shaderID);
}
