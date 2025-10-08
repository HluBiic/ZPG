//#include "App.h"

//GLM test
// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
/*
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
    glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
    glm::vec3(0, 0, 0), // and looks at the origin
    glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f)
*/

/**
* @brief This is the aplication entry point. It creates the App class
* instance and initializes OpenGL, creates shaders / models and runs
* the main rendering loop.
* 
* @author HLU0035
*/

#pragma once
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "sphere.h"

const char* vertex_shader =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 projectMatrix;"
"uniform mat4 viewMatrix;"
"out vec3 vertexColor;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"
"void main () {"
"     vertexColor=vn;"
"     gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 fragColor;"
"in vec3 vertexColor;"
"void main () {"
"     fragColor = vec4(vertexColor, 0.0);"
"}";

glm::vec3 cameraPos = glm::vec3(0.5f, 0.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(-1.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f; // rotation around Y axis, initialized to look toward -X
float pitch = 0.0f;   // rotation around X axis
float lastX = 400, lastY = 300; // initial mouse position
bool firstMouse = true;
bool rightMousePressed = false;
float sensitivity = 0.1f;


int main(void) {
	/*App* a = new App();

	a->initialization();

   a->createScenes();

   a->run();*/


	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	//vbo,vao
	GLuint VBO, VAO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glm::mat4 M = glm::mat4(1.0f);
	float alpha = 0;
	GLint matrixID;
	float temp = 0;

	glEnable(GL_DEPTH_TEST);

	//cam
	glm::vec3 cameraPos = glm::vec3(0.5f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(-1.0f, 0.0f, 0.0f); // looking toward origin
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float cameraSpeed = 0.05f;

	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		temp += 0.1;
		alpha += 0.2;

		//model M
		M = glm::rotate(glm::mat4(1.0f), alpha, glm::vec3(0.0f, 0.0f, 1.0f));
		matrixID = glGetUniformLocation(shaderProgram, "modelMatrix");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(M));
		//view M
		M = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		matrixID = glGetUniformLocation(shaderProgram, "viewMatrix");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(M));
		//projection M
		M = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);
		matrixID = glGetUniformLocation(shaderProgram, "projectMatrix");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(M));

		//camera "walking" movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 2880); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}