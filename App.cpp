#include "App.h"

App* App::appInstance = nullptr;

App::App() {
	this->window = nullptr; // otherwise error "uninitialized variable used"
}

App* App::getInstance() {
	if (appInstance == nullptr) {
		appInstance = new App(); 
	} else {
		printf("App instance already created. Returning original instance.\n");
	}
	return appInstance;
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
	glfwSetWindowUserPointer(this->window, this); //will store the App instance ptr for accessing class members from static callbacks
}

void App::createScenes() {
	this->scenes.emplace_back(Scene());
	this->scenes.emplace_back(Scene());
	this->scenes.emplace_back(Scene());

	this->scenes.at(0).basicScene();
	this->scenes.at(1).symetricalSpheresScene();
	//this->scenes.at(1).allLightShadersTestScene();
	//this->scenes.at(2).forestScene();
	this->scenes.at(2).galaxy();
}

void App::run() {
	glEnable(GL_DEPTH_TEST); // Do depth comparisons and update the depth buff
	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw the currently chosen scene
		if (this->currentScene < this->scenes.size()) {
			this->scenes.at(this->currentScene).draw();
		}

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
	App* app = (App*)glfwGetWindowUserPointer(window);
	app->scenes.at(app->currentScene).camera->mouseMovement(mouseX, mouseY);
}

void App::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	//scene switchinch via 1-3 numerical keys + cam moving with wasd

	App* app = (App*)glfwGetWindowUserPointer(window); // retrieve the app instance to access the scene index 

	if (action == GLFW_PRESS || action == GLFW_REPEAT) { //GLFW_REPEAT - for button holding down
		int newIndex = -1;
		switch (key) {
			case GLFW_KEY_KP_1:
				app->currentScene = 0;
				break;
			case GLFW_KEY_KP_2:
				app->currentScene = 1;
				break;
			case GLFW_KEY_KP_3:
				app->currentScene = 2;
				break;
			case GLFW_KEY_W:
			case GLFW_KEY_A:
			case GLFW_KEY_S:
			case GLFW_KEY_D:
				app->scenes.at(app->currentScene).camera->move(key);
				break;
		}
	}
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

	App* app = (App*)glfwGetWindowUserPointer(window); // retrieve the app instance to access the scene index 
	app->scenes.at(app->currentScene).camera->setViewportSize(width, height);//cam will notify all shader programs about resizing
}

void App::cursor_callback(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
}

void App::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	App* app = (App*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			app->scenes.at(app->currentScene).camera->rotating = true;
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			app->scenes.at(app->currentScene).camera->lastX = (float)x;
			app->scenes.at(app->currentScene).camera->lastY = (float)y;
		}
		else if (action == GLFW_RELEASE) {
			app->scenes.at(app->currentScene).camera->rotating = false;
		}
	}
}