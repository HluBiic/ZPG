#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

/**
* @class ShaderProgram
* @brief
* This class handles creation, compilation and usage of a shader
* program in OpenGl. The ID is private and cannot leave the class,
* or be accessed directly.
* 
* @author HLU0035
*/
class ShaderProgram {
	private:
		GLuint id; // ID which is kept private and never exposed outside this class
	public:
		/**
		* @brief Constructor for the shader program from vertex and fragment shaders.
		* Creates and tests if compilation + linking was successfull.
		* 
		* @param vertexShader Vertex shader passed as text
		* @param fragmentShader Fragment shader passed as text
		*/
		ShaderProgram(const char* vertexShader, const char* fragmentShader);
		//bool setShaderProgram();

		/**
		* @brief Activates the shader program for rendering. Calls glUseProgram()
		* with this shader program's ID so it never leaves the class.
		*/
		void useShaderProgram();
};