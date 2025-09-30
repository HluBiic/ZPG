#pragma once
#include <vector>
#include <GL/glew.h>

using namespace std;

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
		vector<float> detailMod; // vertex position + color data for detailed models

		vector<float> rawData;
		int rawVertCount = 0;
		int floatsPerVert = 0;

		GLuint VAO = 0; // vertex array object
		GLuint VBO = 0; // bertex buffer object
	public:


		/* second contructor for advanced models in LAB03*/
		Model(const float* data, int vertCount, int floatPerVert);



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

		void setupRawModel();

		/**
		* @brief Draws the model and automatically selects between GL_TRIANGLE_STRIP
		* for simple models and GL_TRIANGLE_FAN for detailed models.
		*/
		void draw();
};