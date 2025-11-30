#pragma once
#include <unordered_map>
#include "Model.h"

class ModelManger {
private:
	static unordered_map<string, Model*> models;
public:
	static Model* getModel(const char* name);
	static void clear();
};