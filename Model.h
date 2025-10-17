#pragma once
#include <vector>
#include <GL/glew.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

#include "triangle.h"
#include "square.h"
#include "sphere.h"
#include "suzi_smooth.h"
#include "suzi_flat.h"
#include "bushes.h"
#include "gift.h"
#include "tree.h"
#include "plain.h"

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
		vector<float> rawData;
		int rawVertCount = 0;
		int floatsPerVert = 0;

		GLuint VAO = 0; // vertex array object
		GLuint VBO = 0; // bertex buffer object
	public:
		Model(const float* data, int vertCount, int floatPerVert);

		/**
		* @brief Draws the model and automatically selects between GL_TRIANGLE_STRIP
		* for simple models and GL_TRIANGLE_FAN for detailed models.
		*/
		void draw();
};