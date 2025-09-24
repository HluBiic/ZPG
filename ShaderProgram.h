#pragma once
#include <GL/glew.h>

class ShaderProgram {
	private:
		GLuint id; // MUST stay private !! no getter
	public:
		ShaderProgram(const char* vertexShader, const char* fragmentShader);
		bool setShaderProgram();
		GLuint getId(); // refactor code ... the ID cannot leave the class!!!
};

