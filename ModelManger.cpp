#include "ModelManger.h"
#include "TextureManager.h"

unordered_map<string, Model*> ModelManger::models;

Model* ModelManger::getModel(const char* name) {

	auto item = ModelManger::models.find(name);

	if (item != ModelManger::models.end()) { //model found...already loaded once
		printf("Model %s already loaded\n", name);
		return item->second;
	} else { //model not found...not yet loaded
		Model* m = new Model(name);
		ModelManger::models[name] = m;
		printf("Model %s loaded first time\n", name);
		return m;
	}
}

void ModelManger::clear() {
	ModelManger::models.clear();
}
