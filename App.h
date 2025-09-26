#pragma once

#include "ShaderProgram.h"
#include "Model.h"

using namespace std;

/**
* @class App
* @brief 
* This class manages the App including window creation, shader setup, model
* creation, rendering loop and setting callback methods. For now contains
* shaders as const char* items.
*
* @author HLU0035
*/
class App {
	private:
		GLFWwindow* window; // pointer to the GLFW window
		vector<ShaderProgram> shaderPrograms; // container for shader programs
		vector<Model> models; // container for models
	public:
		/**
		* @brief Initializes the window ptr.
		*/
		App();

		/**
		* @brief OpenGL initialiyation and prints its info + callbacks.
		*/
		void initialization();

		/**
		* @brief Creates and compiles shader programs for the app and adding them 
		* to the shaderPrograms container.
		*/
		void createShaders();

		/**
		* @brief Creates models, sets up their buffers (VBO, VAO) and adds them
		* to the models container.
		*/
		void createModels();

		/**
		* @brief Main rendering loop. Clears buffers, draws models and swaps 
		* buffers (double buffering). Destroys the window before exit.
		*/
		void run();

		/**
		* @brief Custom cursor position callback (LAB02).
		*/
		static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);

		/**
		* @brief GLFW error callback.
		*/
		static void error_callback(int error, const char* description);

		/**
		* @brief GLFW key callback. Handles key presses.
		*/
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		
		/**
		* @brief GLFW window focus callback.
		*/
		static void window_focus_callback(GLFWwindow* window, int focused);
		
		/**
		* @brief GLFW window iconify (minimize/maximize) callback.
		*/
		static void window_iconify_callback(GLFWwindow* window, int iconified);
		
		/**
		* @brief GLFW window resize callback.
		*/
		static void window_size_callback(GLFWwindow* window, int width, int height);
		
		/**
		* @brief GLFW basic cursor callback (LAB01).
		*/
		static void cursor_callback(GLFWwindow* window, double x, double y);
		
		/**
		* @brief GLFW mouse button callback.
		*/
		static void button_callback(GLFWwindow* window, int button, int action, int mode);
};