#pragma once
#include <stdio.h>
#include <cstdlib>
#include <GL/glew.h>
#include <iostream>

#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"

using namespace std;

/**
* @class App
* @brief 
* This class manages the App including window creation, scene setup,
* rendering loop and setting callback methods.
*
* @author HLU0035
*/
class App {
	private:
		GLFWwindow* window; // pointer to the GLFW window
		vector<Scene> scenes; //container for scenes

		int currentScene = 0; //index of the currently drawn scene...0 for the default scene
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
		* @brief Creates scenes and saves them to the scenes vector.
		*/
		void createScenes();

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