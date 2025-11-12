#include "TextureManager.h"

unordered_map<string, Texture*> TextureManager::textures;

Texture* TextureManager::getTexture(const char* name) {
	auto item = TextureManager::textures.find(name);

	if (item != TextureManager::textures.end()) {
		printf("Texture %s already loaded\n", name);
		return item->second;
	}
	else {
		Texture* t = new Texture(name);
		TextureManager::textures[name] = t;
		printf("Texture %s loaded first time\n", name);
		return t;
	}
}

void TextureManager::clear() {
	TextureManager::textures.clear();
}