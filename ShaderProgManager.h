#pragma once
#include "ShaderProgram.h"

using namespace std;

class ShaderProgManager {
private:
	//static vector<ShaderProgram*> shaderPrograms;
public:
	static ShaderProgram* getShaderProgram(const char* verShadFile, const char* fragShadFile);
	static void registerAllObservers(ShaderProgram* sp, Camera* c, Light* l);
	static void registerAllObservers(ShaderProgram* sp, Camera* c, vector<Light*> lights);
};

