#pragma once
#include <unordered_map>
#include "Texture.h"

class TextureManager {
private:
	static unordered_map<string, Texture*> textures;
public:
	static Texture* getTexture(const char* name);
	static void clear();
};

