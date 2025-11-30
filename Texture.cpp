#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"

Texture::Texture(const char* filename) {
	string path = "assets/textures/";
	string fullPath = path + filename;

	stbi_set_flip_vertically_on_load(true);
	this->type = GL_TEXTURE_2D;

	//last argument is the desired number of color channels to be loaded
	this->textureData = stbi_load(fullPath.c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);

	if (!this->textureData) {
		printf("Error loading texture: %s\n", filename);
		return;
	}

	//creating the texture
	glGenTextures(1, &this->tex);
	glBindTexture(this->type, this->tex); //bind the texture the the unit
	glTexImage2D(this->type, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	glGenerateMipmap(this->type);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT); //mipmaps...texture repeating
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //2x interpolated
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_LINEAR=blur effect


	stbi_image_free(this->textureData);//texture done...dont need the image anymore
}

Texture::Texture() {
	string path = "assets/textures/";

	stbi_set_flip_vertically_on_load(false);
	this->type = GL_TEXTURE_CUBE_MAP;
	
	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &this->tex);
	glBindTexture(this->type, this->tex);

	//const char

	//for (int i = 0; i < 6; i++) {
	//	string fullPath = path + facesFilenames[i];
	//	this->textureData = stbi_load(fullPath.c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	//}

	this->textureData = stbi_load((path + "posx.jpg").c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	if (!this->textureData) {
		printf("Error loading texture: posx\n");
		return;
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	stbi_image_free(this->textureData);


	this->textureData = stbi_load((path + "negx.jpg").c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	if (!this->textureData) {
		printf("Error loading texture: negx\n");
		return;
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	stbi_image_free(this->textureData);

	this->textureData = stbi_load((path + "posy.jpg").c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	if (!this->textureData) {
		printf("Error loading texture: posy\n");
		return;
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	stbi_image_free(this->textureData);

	this->textureData = stbi_load((path + "negy.jpg").c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	if (!this->textureData) {
		printf("Error loading texture: negy\n");
		return;
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	stbi_image_free(this->textureData);

	this->textureData = stbi_load((path + "posz.jpg").c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	if (!this->textureData) {
		printf("Error loading texture: posz\n");
		return;
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	stbi_image_free(this->textureData);

	this->textureData = stbi_load((path + "negz.jpg").c_str(), &this->textureWidth, &this->textureHeight, &this->channels, 4);
	if (!this->textureData) {
		printf("Error loading texture: negz\n");
		return;
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, this->textureWidth, this->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
	stbi_image_free(this->textureData);

	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void Texture::bind(GLuint textUnitId) {
	glActiveTexture(GL_TEXTURE0 + textUnitId); //selecting texture unit on the GPU
	//printf("Used texture unit: %d\n",this->tex);
	//glBindTexture(GL_TEXTURE_2D, this->tex);
	glBindTexture(this->type, this->tex);
}

void Texture::unbind() {
	//printf("Unused %d texture unit\n", this->tex);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(this->type, 0);
}
