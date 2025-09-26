#pragma once
#include <vector>
#include <GL/glew.h>

using namespace std;

/**
* @struct Vertex
* @brief Represents data about a vertex position and color. 
* 
* Each vertex contains:
* - pos: x, y, z, w
* - col: r, g, b, a
*/
struct Vertex {
	float pos[4];
	float col[4];
};

/**
* @class Model
* @brief
* This class represents a simple (triangle, circle, rectangle) or detailed
* model with colors. It provides functions to set up VBO, VAO and draw the
* models using the correct OpenGL methods.
*
* @author HLU0035
*/
class Model {
	private:
		vector<float> simpleMod; // vertex position data for simple models (x,y,z)
		vector<Vertex> detailMod; // vertex position + color data for detailed models
		GLuint VAO = 0; // vertex array object
		GLuint VBO = 0; // bertex buffer object
	public:
		/**
		* @brief Construstor for the Model with a specific type.
		* @param type Int specifying the type pof model:
		*	1 - rectangle in center
		*	2 - tringle on top right
		*	3 - circle
		*	4 - rectangle with colors (detailed model)
		*/
		Model(int type);

		/**
		* @brief Prepares simple model vertex data for render using VBO, VAO.
		*/
		void setupSimpleModel();

		/**
		* @brief Prepares detailed model (with position and colors) vertex data 
		* for render using VBO, VAO. Sets attribute pointers for position 
		* (location 0) and color (location 1).
		*/
		void setupDetailedModel();

		/**
		* @brief Draws the model and automatically selects between GL_TRIANGLE_STRIP
		* for simple models and GL_TRIANGLE_FAN for detailed models.
		*/
		void draw();
};