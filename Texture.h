#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

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

	GLenum type = GL_TEXTURE_2D;

	//loads + creates the texture from file
	Texture(const char* filename);
	//loads + creates the texture for cubemap skybox
	Texture();
	//binds the texture unit on GPU with the texture
	void bind(GLuint textUnitId);
	void unbind();
};

