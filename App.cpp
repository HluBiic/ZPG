#include <stdio.h>
#include <cstdlib>
#include <GL/glew.h>

#include "App.h"
#include "ShaderProgram.h"
#include "Model.h"

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* vertex_shader_detail =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec4 vc;"
"out vec4 vertexColor;" //passing color to frag. shader
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  vertexColor = vc;"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.0, 0.5, 0.5, 1.0);"
"}";

const char* fragment_shader2 =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.0, 0.8, 0.1, 1.0);"
"}";

const char* fragment_shader_detail =
"#version 330\n"
"in vec4 vertexColor;" //received from vert. shader
"out vec4 fragColor;"
"void main () {"
"     fragColor = vertexColor;"
"}";

App::App() {
	this->window = nullptr; // otherwise error "uninitialized variable used"
}

void App::initialization() {
	if (!glfwInit()) {
		fprintf(stderr, "APP::ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	} else {
		printf("APP::GLFW3 initialized successully\n");
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1); // v-sync enable

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	// Initial setup of size, buffer size, viewport
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	// Registers all the callbacks
	glfwSetErrorCallback(this->error_callback);
	glfwSetKeyCallback(this->window, this->key_callback);
	glfwSetCursorPosCallback(this->window, this->cursor_pos_callback);
	glfwSetMouseButtonCallback(this->window, this->button_callback);
	glfwSetWindowFocusCallback(this->window, this->window_focus_callback);
	glfwSetWindowIconifyCallback(this->window, this->window_iconify_callback);
	glfwSetWindowSizeCallback(this->window, this->window_size_callback);
}

void App::createShaders() {
	//emplace .. constructs the element and pushes to vector .. needed because of ID in shader
	this->shaderPrograms.emplace_back(ShaderProgram(vertex_shader, fragment_shader));
	this->shaderPrograms.emplace_back(ShaderProgram(vertex_shader_detail, fragment_shader_detail));
}

void App::createModels() {
	this->models.emplace_back(Model(2));
	this->models.at(0).setupSimpleModel();

	this->models.emplace_back(Model(4));
	this->models.at(1).setupDetailedModel();
}

void App::run() {
	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// detailed model ... from LAB2 square with colors
		this->shaderPrograms.at(1).useShaderProgram();
		this->models.at(1).draw();

		// simple model ... triangle on right side
		this->shaderPrograms.at(0).useShaderProgram();
		this->models.at(0).draw();

		// update other events like input handling
		glfwPollEvents(); // For procesing any pending input events (nmouse, keyboard, window)

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window); // swap buffer...double buffering for rendering
	}
	glfwDestroyWindow(this->window); // Destroy wind. before exiting program

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void App::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY );
}

void App::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void App::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void App::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void App::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void App::cursor_callback(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
}

void App::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}
