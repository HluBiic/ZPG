#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"

Texture::Texture(const char* filename) {
	string path = "assets/textures/";
	string fullPath = path + filename;

	stbi_set_flip_vertically_on_load(true);

	//last argument -> desired number of color channels to be loaded
	this->textureData = stbi_load(fullPath.c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);

	if (!this->textureData) {
		printf("Error loading texture: %s\n", filename);
		return;
	}

	//creating the texture
	glGenTextures(1, &this->tex);
	glBindTexture(GL_TEXTURE_2D, this->tex); //bind the texture the the unit
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	stbi_image_free(this->textureData);//texture done...dont need the image anymore
}

void Texture::bind(GLuint textUnitId) {
	glActiveTexture(GL_TEXTURE0 + textUnitId); //selecting texture unit on the GPU
	//printf("Used texture unit: %d\n",this->tex);
	glBindTexture(GL_TEXTURE_2D, this->tex);
}

void Texture::unbind() {
	//printf("Unused %d texture unit\n", this->tex);
	glBindTexture(GL_TEXTURE_2D, 0);
}
