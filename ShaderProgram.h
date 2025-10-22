#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IObserver.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"

using namespace std;

/**
* @class ShaderProgram
* @brief
* This class handles creation, compilation and usage of a shader
* program in OpenGl. The ID is private and cannot leave the class,
* or be accessed directly.
* 
* @author HLU0035
*/
//class Camera;
class ShaderProgram : public IObserver /*public ICamObserver, public ILightObserver*/ {
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
		ShaderProgram(Shader* vertexShader, Shader* fragmentShader);

		/**
		* @brief Activates the shader program for rendering. Calls glUseProgram()
		* with this shader program's ID so it never leaves the class.
		*/
		void useShaderProgram();

		void setUniform(const char* name, const glm::mat4& matrix);
		void setUniform(const glm::mat4& matrix);
		void setUniform(const char* name, const glm::vec3&);

		//void camUpdated(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 camPosition) override;
		//void lightUpdate(glm::vec3 lightPos) override;
		void update(ObserverSubject* s) override;

		// ONLY FOR TESTING PURPOSES !!!
		/*GLuint getId() {
			printf( "CAREFULL getId ONLY FOR TESTING PURPOSES remove / comment out before submission of homework!!!!\n");
			return this->id;
		}*/
};
