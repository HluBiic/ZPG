#include "Scene.h"

Scene::Scene() {
	this->camera = nullptr;
}

//LAB 03 - TASK 5 - simple spinning triangle
void Scene::basicScene() {
	TransformGroup* tg = new TransformGroup();
	tg->add(new Scale(glm::vec3(0.3f)));
	//tg->add(new Spin(180.0f, glm::vec3(0.0f, 0.0f, 1.0f))); // spinning 180 degrees per second
	tg->add(new Rotation(23.0f, glm::vec3(0.0f, 0.0f,  1.0f)));
	tg->add(new Translation(glm::vec3(2.0f, -0.5f, 0.0f)));

	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(triangle, size(triangle), 6),
			tg
		)
	);
}

//LAB 3 - TASK 6 - 4x spheres symetricaly placed along axes
void Scene::sceneTask6() {
	TransformGroup* tg1 = new TransformGroup();
	tg1->add(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	tg1->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg2 = new TransformGroup();
	tg2->add(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	tg2->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg3 = new TransformGroup();
	tg3->add(new Translation(glm::vec3(2.0f, 0.0f, 0.0f)));
	tg3->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg4 = new TransformGroup();
	tg4->add(new Translation(glm::vec3(-2.0f, 0.0f, 0.0f)));
	tg4->add(new Scale(glm::vec3(0.1f)));

	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(sphere, size(sphere), 6),
			tg1
		)
	);
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(sphere, size(sphere), 6),
			tg2
		)
	);
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(sphere, size(sphere), 6),
			tg3
		)
	);
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(sphere, size(sphere), 6),
			tg4
		)
	);
}

//LAB 3 - TASK 7 - scene with at least 20 objects; various models, transformations, shader programs
void Scene::sceneTask7() {
	float xTreeOffset = -18.0f;
	float xGiftOffset = -1.5f;
	float giftAngleOffset = 10.0f;

	// 10 trees
	for (int i = 0; i < 10; i++) {
		TransformGroup* tg = new TransformGroup();
		tg->add(new Translation(glm::vec3(xTreeOffset, 3.0f, 0.0f)));
		tg->add(new Scale(glm::vec3(0.05f)));				

		xTreeOffset += 4.0f;

		DrawableObject* dwo = new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(tree, size(tree), 6),
			tg
		);
		this->objects.push_back(dwo);
	}
	// 5 gifts 
	for (int i = 0; i < 5; i++) {		
		TransformGroup* tg = new TransformGroup();	
		tg->add(new Translation(glm::vec3(xGiftOffset, -0.5f, 0.0f)));
		tg->add(new Scale(glm::vec3(0.35f)));		

		xGiftOffset += 0.8f;

		DrawableObject* dwo = new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(gift, size(gift), 6),
			tg
		);
		this->objects.push_back(dwo);
	}
	// 1x sun, 1x moon
	TransformGroup* tg1 = new TransformGroup();
	tg1->add(new Translation(glm::vec3(-4.5f, 4.5f, 0.0f)));
	tg1->add(new Scale(glm::vec3(0.2f)));
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform_color, fragment_shader_detail_color_grey),
			new Model(sphere, size(sphere), 6),
			tg1
		)
	);
	TransformGroup* tg2 = new TransformGroup();
	tg2->add(new Translation(glm::vec3(4.5f, 4.5f, 0.0f)));
	tg2->add(new Scale(glm::vec3(0.2f)));
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail_color_yellow),
			new Model(sphere, size(sphere), 6),
			tg2
		)
	);

	// 2x bush
	TransformGroup* tg3 = new TransformGroup();
	tg3->add(new Translation(glm::vec3(-1.5f, -2.0f, 0.0f)));
	tg3->add(new Scale(glm::vec3(0.5f)));
	TransformGroup* tg4 = new TransformGroup();
	tg4->add(new Translation(glm::vec3(1.5f, -2.0f, 0.0f)));
	tg4->add(new Scale(glm::vec3(0.5f)));
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform_color, fragment_shader_detail_color_green),
			new Model(bushes, size(bushes), 6),
			tg3
		)
	);
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform_color, fragment_shader_detail_color_green),
			new Model(bushes, size(bushes), 6),
			tg4
		)
	);

	// 1x suzi
	TransformGroup* tg5 = new TransformGroup();
	tg5->add(new Translation(glm::vec3(0.5f, -2.5f, 0.0f)));
	tg5->add(new Spin(45, glm::vec3(0.0f, 0.0f, 1.0f)));
	tg5->add(new Scale(glm::vec3(0.2f)));
	this->objects.push_back(
		new DrawableObject(
			new ShaderProgram(vertex_shader_uniform, fragment_shader_detail),
			new Model(suziFlat, size(suziFlat), 6),
			tg5
		)
	);
}

void Scene::cameraScene() {
	this->camera = new Camera();
	ShaderProgram* sp = new ShaderProgram(vertex_shader_camera, fragment_shader_camera);
	this->camera->registerObserver(sp);

	Model* treeModel = new Model(tree, size(tree), 6);
	Model* bushModel = new Model(bushes, size(bushes), 6);

	float xTreeOffset = 0.0f;
	float yTreeBushOffset = 0.0f;//same for all trees + bushes
	float zTreeOffset = 0.0f;

	float xBushOffset = 0.0f;
	float zBushOffest = 0.0f;

	for (int i = 0; i < 50; i++) {
		//get rand x and z offsets
		xTreeOffset = 0.5f + (float)(rand()) / RAND_MAX * (60.0f - 0.5f);
		zTreeOffset = 0.5f + (float)(rand()) / RAND_MAX * (60.0f - 0.5f);
		xBushOffset = 0.5f + (float)(rand()) / RAND_MAX * (20.0f - 0.5f);
		zBushOffest = 0.5f + (float)(rand()) / RAND_MAX * (20.0f - 0.5f);

		//50 tree objects
		TransformGroup* tgTree = new TransformGroup();
		tgTree->add(new Translation(glm::vec3(xTreeOffset, yTreeBushOffset, zTreeOffset)));
		tgTree->add(new Scale(glm::vec3(0.1f)));
		this->objects.push_back(
			new DrawableObject(
				sp, treeModel, tgTree
			)
		);

		//50 bushes objects
		TransformGroup* tgBush = new TransformGroup();
		tgBush->add(new Translation(glm::vec3(xBushOffset, yTreeBushOffset, zBushOffest)));
		tgBush->add(new Scale(glm::vec3(0.3f)));
		this->objects.push_back(
			new DrawableObject(
				sp, bushModel, tgBush
			)
		);
	}
}

void Scene::addObject(DrawableObject* drawObj) {
	this->objects.push_back(drawObj);
}


void Scene::draw() {
	for (auto o : this->objects) {
		o->draw();
	}
	this->camera->notifyObservers();
}

void Scene::moveCam(int key) {
	this->camera->move(key);
}
