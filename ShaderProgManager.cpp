#include "ShaderProgManager.h"

//vector<ShaderProgram*> ShaderProgManager::shaderPrograms;

ShaderProgram* ShaderProgManager::getShaderProgram(const char* verShadFile, const char* fragShadFile) {
	Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, verShadFile);

	Shader* fragmentShader = new Shader();
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, fragShadFile);

	ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);
	if (sp != nullptr) {
		return sp;
	}
    return nullptr;
}

void ShaderProgManager::registerAllObservers(ShaderProgram* sp, Camera* c, Light* l) {
	c->registerObserver(sp);
	l->registerObserver(sp);
}

void ShaderProgManager::registerAllObservers(ShaderProgram* sp, Camera* c, vector<Light*> lights) {
	c->registerObserver(sp);
	for (auto l : lights) {
		l->registerObserver(sp);
	}
}
