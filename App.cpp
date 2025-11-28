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
	//int width, height;
	glfwGetFramebufferSize(this->window, &this->currentWidth, &this->currentHeight);
	float ratio = this->currentWidth / (float)this->currentHeight;
	glViewport(0, 0, this->currentWidth, this->currentHeight);

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
	this->scenes.emplace_back(Scene());
	this->scenes.emplace_back(Scene());

	//this->scenes.at(0).basicScene();
	this->scenes.at(0).tryoutScene();
	//this->scenes.at(0).testScene();
	this->scenes.at(1).symetricalSpheresScene();
	//this->scenes.at(1).allLightShadersTestScene();
	this->scenes.at(2).galaxy();
	this->scenes.at(3).forestScene();
	this->scenes.at(4).whacAMole();
}

void App::run() {
	glEnable(GL_DEPTH_TEST); // Do depth comparisons and update the depth buff
	glEnable(GL_STENCIL_TEST); //stencil buffer will contain ids of the drawable objects

	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		/*for (auto obj : this->scenes.at(this->currentScene).objects) {
			glStencilFunc(GL_ALWAYS, obj->getID(), 0xFF);
		}...moved to Scene::draw bcs stencil buffer showed not id but total number of DrawableObjects*/

		// draw the currently chosen scene
		if (this->currentScene < this->scenes.size()) {
			this->scenes.at(this->currentScene).drawSkybox();
			this->scenes.at(this->currentScene).draw();
		}



		// update other events like input handling
		glfwPollEvents(); // For procesing any pending input events (nmouse, keyboard, window)

		// put the stuff weve been drawing onto the display
		glfwSwapBuffers(this->window); // swap buffer...double buffering for rendering
	}
	glfwDestroyWindow(this->window); // Destroy wind. before exiting program

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void App::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY );
	App* app = (App*)glfwGetWindowUserPointer(window);
	app->scenes.at(app->currentScene).camera->mouseMovement(mouseX, mouseY);
}

void App::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	//scene switchinch via 1-3 numerical keys + cam moving with wasd

	App* app = (App*)glfwGetWindowUserPointer(window); // retrieve the app instance to access the scene index 
	glfwGetFramebufferSize(window, &app->currentWidth, &app->currentHeight); //so that size is current not only after resize but also between scene switching
	app->scenes.at(app->currentScene).camera->setViewportSize(app->currentWidth, app->currentHeight);

	if (action == GLFW_PRESS || action == GLFW_REPEAT) { //GLFW_REPEAT - for button holding down
		int newIndex = -1;
		switch (key) {
			case GLFW_KEY_KP_1:
				app->currentScene = 0;
				//app->scenes.at(app->currentScene).camera->setViewportSize(window, height);//cam will notify all shader programs about resizing
				break;
			case GLFW_KEY_KP_2:
				app->currentScene = 1;
				break;
			case GLFW_KEY_KP_3:
				app->currentScene = 2;
				break;
			case GLFW_KEY_KP_4:
				app->currentScene = 3;
				break;
			case GLFW_KEY_KP_5:
				app->currentScene = 4;
				break;
			case GLFW_KEY_W:
			case GLFW_KEY_A:
			case GLFW_KEY_S:
			case GLFW_KEY_D:
				app->scenes.at(app->currentScene).camera->move(key);
				break;
			case GLFW_KEY_R:
				if (app->deleteToggled) {
					app->deleteToggled = false;
					printf("DELETE MODE OFF\n");
				} else {
					app->deleteToggled = true;
					printf("DELETE MODE ON\n");
				}
				break;
			case GLFW_KEY_B:
				if (app->pathingToggled) {
					app->pathingToggled = false;
					printf("BEZIER POINTS MODE OFF\n");
					//app->scenes.at(app->currentScene).printAllBezierPoints();
					app->scenes.at(app->currentScene).cropBezierPoints();
					app->scenes.at(app->currentScene).printAllBezierPoints();
					//app->scenes.at(app->currentScene).bezierPoints.clear();
				} else {
					app->pathingToggled = true;
					printf("BEZIER POINTS MODE ON\n");
				}
				break;
			case GLFW_KEY_F:
				int isEnabled = app->scenes.at(app->currentScene).flashlight->flashlightEnabled;
				if (isEnabled == 1) {
					app->scenes.at(app->currentScene).flashlight->flashlightEnabled = 0;
				} else {
					app->scenes.at(app->currentScene).flashlight->flashlightEnabled = 1;
				}
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
	app->currentHeight = height;
	app->currentWidth = width;
	app->scenes.at(app->currentScene).camera->setViewportSize(width, height);//cam will notify all shader programs about resizing
}

void App::cursor_callback(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
}

void App::button_callback(GLFWwindow* window, int button, int action, int mode) {
	//if (action == GLFW_PRESS); printf("button_callback [%d,%d,%d]\n", button, action, mode);
	App* app = (App*)glfwGetWindowUserPointer(window);
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			app->scenes.at(app->currentScene).camera->rotating = true;

			app->scenes.at(app->currentScene).camera->lastX = (float)x;
			app->scenes.at(app->currentScene).camera->lastY = (float)y;

			if (app->deleteToggled) { //only after "R" was pressed previously
				//object deleting after right click
				GLbyte color[4];
				GLfloat depth;
				GLuint index;
				int newy = app->scenes.at(app->currentScene).camera->getResolution().y - y;
				glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
				glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
				glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
				//printf("Clicked on pixel %g, %g, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
				//%g supresses tailing zeros so 123.000 -> 123

				app->scenes.at(app->currentScene).setInactiveDrawObj(index);
			}

		}
		else if (action == GLFW_RELEASE) {
			app->scenes.at(app->currentScene).camera->rotating = false;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {

			GLfloat depth;
			int newy = app->scenes.at(app->currentScene).camera->getResolution().y - y;
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

			glm::vec3 screenX = glm::vec3(x, newy, depth);
			glm::mat4 view = app->scenes.at(app->currentScene).camera->getViewMatrix();
			glm::mat4 projection = app->scenes.at(app->currentScene).camera->getProjectionMatrix();
			glm::vec2 camResolution = app->scenes.at(app->currentScene).camera->getResolution();
			glm::vec4 viewPort = glm::vec4(0, 0, camResolution.x, camResolution.y);
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
			//printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

			if (!app->pathingToggled) {
				app->scenes.at(app->currentScene).growNewTree(pos);
			} else {
				app->scenes.at(app->currentScene).bezierPoints.push_back(pos);
			}
		}
	}
}