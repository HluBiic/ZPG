#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class Texture {
private:

public:
	unsigned char* textureData;
	int textureWidth;
	int textureHeight;
	int channels;

	GLuint textureUnitId = 0;
	GLuint tex = 0;

	//loads + creates the texture from file
	Texture(const char* filename);
	//binds the texture unit on GPU with the texture
	void bind(GLuint textUnitId);
	void unbind();
};

