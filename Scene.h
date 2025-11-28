#pragma once
#include "DrawableObject.h"
#include "TransformationComposite.h"
#include "Camera.h"
#include "Light.h"
#include "ModelManger.h"
#include "TextureManager.h"
#include "ShaderProgManager.h"

//bcs MULTIPLE times mistakes when writing the filename :)
//constexpr const char* VERTEX_SHADER = "vertex_shader.glsl";
//constexpr const char* CONSTANT_FRAGMENT_SHADER = "constant_fragment_shader.glsl";
constexpr const char* LAMBERT_FRAGMENT_SHADER = "lambert_fragment_shader.glsl";
constexpr const char* PHONG_CORRECT_FRAGMENT_SHADER = "phong_correct_fragment_shader.glsl";
constexpr const char* PHONG_INCORRECT_FRAGMENT_SHADER = "phong_incorrect_fragment_shader.glsl";
constexpr const char* BLINN_FRAGMENT_SHADER = "blinn_fragment_shader.glsl";
constexpr const char* TEXTURE_FRAGMENT_SHADER = "texture_fragment_shader.glsl";
constexpr const char* MULTI_FRAGMENT_SHADER = "multi_fragment_shader.glsl";
constexpr const char* SKYBOX_FRAGMENT_SHADER = "skybox_fragment_shader.glsl";
constexpr const char* SKYBOX_VERTEX_SHADER = "skybox_vertex_shader.glsl";

class Scene {
private:
	
public:
	Camera* camera;
	vector<Light*> lights;
	Light* flashlight;
	vector<DrawableObject*> objects;

	DrawableObject* growableTreeModel;
	ShaderProgram* spNewMoles;

	DrawableObject* skybox;

	vector<glm::vec3> bezierPoints;

	int score = 0;
	string sceneType;

	Scene();
	void tryoutScene();
	void testScene();
	void basicScene();
	void symetricalSpheresScene();
	void forestScene();
	void galaxy();
	void whacAMole();
	void addObject(DrawableObject* drawObj);

	void draw();

	void moveCam(int key);

	void setInactiveDrawObj(int id);
	void growNewTree(glm::vec3 position);
	void spawnNewMole(int type);

	void printAllBezierPoints();
	void cropBezierPoints();

	void drawSkybox();
	//void printAllFilteredBezierPoints();
};