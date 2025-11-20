#pragma once
#include "DrawableObject.h"
#include "TransformGroup.h"
#include "Camera.h"
#include "Light.h"
#include "ModelManger.h"
#include "TextureManager.h"
#include "ShaderProgManager.h"

//bcs MULTIPLE times mistakes when writing the filename :)
//constexpr const char* VERTEX_SHADER = "vertex_shader.glsl";
constexpr const char* TEXTURE_VERTEX_SHADER = "texture_vertex_shader.glsl";
//constexpr const char* CONSTANT_FRAGMENT_SHADER = "constant_fragment_shader.glsl";
constexpr const char* LAMBERT_FRAGMENT_SHADER = "lambert_fragment_shader.glsl";
constexpr const char* PHONG_CORRECT_FRAGMENT_SHADER = "phong_correct_fragment_shader.glsl";
constexpr const char* PHONG_INCORRECT_FRAGMENT_SHADER = "phong_incorrect_fragment_shader.glsl";
constexpr const char* BLINN_FRAGMENT_SHADER = "blinn_fragment_shader.glsl";
constexpr const char* TEXTURE_FRAGMENT_SHADER = "texture_fragment_shader.glsl";


class Scene {
private:
	
public:
	Camera* camera;
	vector<Light*> lights;
	Light* flashlight;
	vector<DrawableObject*> objects;

	DrawableObject* growableTreeModel;

	int score = 0;

	Scene();
	void tryoutScene();
	void basicScene();
	void symetricalSpheresScene();
	void allLightShadersTestScene();
	void forestScene();
	void galaxy();
	void whacAMole();
	void addObject(DrawableObject* drawObj);

	void draw();

	void moveCam(int key);

	void setInactiveDrawObj(int id);
	void growNewTree(glm::vec3 position);
};