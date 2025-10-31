#include "Scene.h"

Scene::Scene() {
	this->camera = new Camera();

	//blueish light...[0]
	this->lights.push_back(new Light(
		glm::vec3(50.0, 50.0, 0.0), //pos
		glm::vec4(0.0, 0.0, 1.0, 1.0), //diff col
		glm::vec4(0.729, 0.729, 0.949, 1.0), //spec col
		1.0f, 0.0f, 0.0f)); //light attenuation

	//redish light...[1]
	this->lights.push_back(new Light(
		glm::vec3(10.0, 10.0, 0.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.929, 0.729, 0.729, 1.0),
		1.0f, 0.0f, 0.0f));

	//main light for forest scene...moon high above teh scene ...[2]
	this->lights.push_back(new Light(
		glm::vec3(20.0f, 20.0f, 0.0f),
		glm::vec4(0.8f, 0.8f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f, 0.0f, 0.01f));

	//firefflies for the forest scene...scatterred arround the forest...[3-12]
	for (int i = 0; i < 10; i++) {
		float x = 0.5f + (float)(rand()) / RAND_MAX * (5.0f - 0.2f);
		float y = 0.08f;
		float z = 0.5f + (float)(rand()) / RAND_MAX * (5.0f - 0.2f);
		this->lights.push_back(new Light(
			glm::vec3(x, y, z),
			glm::vec4(0.5f, 0.8f, 0.2f, 1.0f),
			glm::vec4(0.5f, 0.8f, 0.2f, 1.0f),
			//1.0f, 0.09f, 0.032f)); extremely much
			//1.0f, 0.9f, 3.8f)); //best so far
			1.0f, 0.0f, 50.0f));//with desmos...best
			//1.0f, 0.35f, 0.44f));toomuch
	}

	//lights for tryout scene...just testing their functionality
	this->lights.push_back(new Light(glm::vec4(0.0, 1.0, 0.0, 1.0)));// ...[13]...AMBIENT
	this->lights.push_back(new Light(
		glm::vec3(-1.0f, -1.0f, -0.5f), 
		glm::vec4(0.0, 0.0, 1.0, 1.0), 
		glm::vec4(0.729, 0.729, 0.949, 1.0)));// ...[14]...DIRECTIONAL


	float innerCutOff = glm::cos(glm::radians(9.0f));
	float outerCutOff = glm::cos(glm::radians(10.0f));
	this->lights.push_back(new Light(// ...[15]...SPOTLIGHT...DOESNT WORK
		glm::vec3(0.0f, 2.0f, 2.0f),
		glm::vec3(0.0f, -1.0f, -1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		innerCutOff, outerCutOff,
		1.0f, 0.09f, 0.032f
	));
}

void Scene::tryoutScene() {
	Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShader = new Shader();
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);

	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	this->camera->registerObserver(sp);
	this->lights.at(14)->registerObserver(sp);
	//this->flashlight->registerObserver(sp);

	Model* m = new Model(sphere, size(sphere), 6);

	TransformGroup* tg = new TransformGroup();
	tg->add(new Scale(glm::vec3(0.2f)));

	this->objects.push_back(new DrawableObject(sp, m, tg));
}

//LAB 05 - TASK 3a - simple static triangle
void Scene::basicScene() {
	Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShader = new Shader();
	//fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, CONSTANT_FRAGMENT_SHADER);...for basic triangle
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	TransformGroup* tgM = new TransformGroup();
	tgM->add(new Scale(glm::vec3(0.2f)));

	TransformGroup* tgZPG = new TransformGroup();
	tgZPG->add(new Translation(glm::vec3(0.0f, -4.0f, -1.0f)));
	tgZPG->add(new Scale(glm::vec3(0.2f)));
	tgZPG->add(new Rotation(45.0f, glm::vec3(1.0, 1.0, 0.0)));

	TransformGroup* tgLogin = new TransformGroup();
	tgLogin->add(new Translation(glm::vec3(0.0f, -4.0f, 1.0f)));
	tgLogin->add(new Scale(glm::vec3(0.2f)));
	tgLogin->add(new Rotation(90.0f, glm::vec3(0.0, 1.0, 1.0)));

	this->camera->registerObserver(sp);
	this->lights.at(0)->registerObserver(sp);

	//Model* m = new Model(triangle, size(triangle), 6);...for basic triangle
	Model* m = new Model("house.obj");
	Model* m2 = new Model("Login.obj");
	Model* m3 = new Model("ZPG Title.obj");

	this->objects.push_back(new DrawableObject(sp, m, tgM));
	this->objects.push_back(new DrawableObject(sp, m3, tgZPG));
	this->objects.push_back(new DrawableObject(sp, m2, tgLogin));
}

//LAB 05 - TASK 3b - 4x spheres symetricaly placed along axes
void Scene::symetricalSpheresScene() {
	Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShader = new Shader();
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	this->camera->registerObserver(sp);
	//this->lights.at(0)->registerObserver(sp);
	for (auto l : lights) {
		l->registerObserver(sp);
	}

	Model* m = new Model(sphere, size(sphere), 6);

	TransformGroup* tg1 = new TransformGroup();
	tg1->add(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	tg1->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg2 = new TransformGroup();
	tg2->add(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	tg2->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg3 = new TransformGroup();
	tg3->add(new Translation(glm::vec3(0.0f, 0.0f, 2.0f)));
	tg3->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg4 = new TransformGroup();
	tg4->add(new Translation(glm::vec3(0.0f, 0.0f, -2.0f)));
	tg4->add(new Scale(glm::vec3(0.1f)));

	this->objects.push_back(new DrawableObject(sp, m, tg1));
	this->objects.push_back(new DrawableObject(sp, m, tg2));
	this->objects.push_back(new DrawableObject(sp, m, tg3));
	this->objects.push_back(new DrawableObject(sp, m, tg4));
}

// LAB 05 - TASK 02 - 4 spheres with 4 basic lightning models
void Scene::allLightShadersTestScene() {
	Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);

	Shader* fragmentShader = new Shader();
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, CONSTANT_FRAGMENT_SHADER);
	ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);

	Shader* fragmentShader2 = new Shader();
	fragmentShader2->createShaderFromFile(GL_FRAGMENT_SHADER, LAMBERT_FRAGMENT_SHADER);
	ShaderProgram* sp2 = new ShaderProgram(vertexShader, fragmentShader2);

	Shader* fragmentShader3 = new Shader();
	fragmentShader3->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	ShaderProgram* sp3 = new ShaderProgram(vertexShader, fragmentShader3);

	Shader* fragmentShader4 = new Shader();
	fragmentShader4->createShaderFromFile(GL_FRAGMENT_SHADER, BLINN_FRAGMENT_SHADER);
	ShaderProgram* sp4 = new ShaderProgram(vertexShader, fragmentShader4);

	this->camera->registerObserver(sp);
	this->camera->registerObserver(sp2);
	this->camera->registerObserver(sp3);
	this->camera->registerObserver(sp4);

	this->lights.at(0)->registerObserver(sp);
	this->lights.at(0)->registerObserver(sp2);
	this->lights.at(0)->registerObserver(sp3);
	this->lights.at(0)->registerObserver(sp4);

	Model* m = new Model(sphere, size(sphere), 6);

	TransformGroup* tg1 = new TransformGroup();//down
	tg1->add(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	tg1->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg2 = new TransformGroup();//up
	tg2->add(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	tg2->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg3 = new TransformGroup();//left
	tg3->add(new Translation(glm::vec3(0.0f, 0.0f, 2.0f)));
	tg3->add(new Scale(glm::vec3(0.1f)));

	TransformGroup* tg4 = new TransformGroup();//right
	tg4->add(new Translation(glm::vec3(0.0f, 0.0f, -2.0f)));
	tg4->add(new Scale(glm::vec3(0.1f)));

	this->objects.push_back(new DrawableObject(sp3, m, tg1));//down will have phong
	this->objects.push_back(new DrawableObject(sp, m, tg2));//up will have constant light
	this->objects.push_back(new DrawableObject(sp4, m, tg3));//left will have blinn-phong
	this->objects.push_back(new DrawableObject(sp2, m, tg4));//right will have lambert
}

//LAB 05 - TASK 3c - forest with bushes and ground
void Scene::forestScene() {
	fflush(stdout);
	Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShader = new Shader();
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	this->camera->registerObserver(sp);

	this->lights.at(2)->registerObserver(sp); //moon/sun
	for (int i = 3; i < 13; i++) { //fireflies
		this->lights.at(i)->registerObserver(sp);
	}

	Model* treeModel = new Model(tree, size(tree), 6);
	Model* bushModel = new Model(bushes, size(bushes), 6);
	Model* ground = new Model(plain, size(plain), 6);
	Model* firefly = new Model(sphere, size(sphere), 6);

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

	//sphere for fireflies...constant shader of white color
	Shader* vertexShaderFirefly = new Shader();
	vertexShaderFirefly->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShaderFirefly = new Shader();
	fragmentShaderFirefly->createShaderFromFile(GL_FRAGMENT_SHADER, CONSTANT_FRAGMENT_SHADER);
	ShaderProgram* spFirefly = new ShaderProgram(vertexShaderFirefly, fragmentShaderFirefly);

	this->camera->registerObserver(spFirefly);
	spFirefly->setUniform("objectColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//glm::vec3 maxDist(0.2f, 0.2f, 0.2f);

	for (int i = 3; i < 13; i++) {
		//PointLight* pl = dynamic_cast<PointLight*>(this->lights.at(i));

		TransformGroup* tgFirefly = new TransformGroup();
		tgFirefly->add(new Scale(glm::vec3(0.008f))); // make it bigger
		//tgFirefly->add(new Translation(pl->lightPosition));
		tgFirefly->add(new Translation(this->lights.at(i)->lightPosition));
		//tgFirefly->add(new RandTranslateDynamic(this->lights.at(i)->lightPosition, maxDist));

		this->objects.push_back(new DrawableObject(spFirefly, firefly, tgFirefly));
	}

	//ground
	TransformGroup* tgGround = new TransformGroup();
	tgGround->add(new Translation(glm::vec3(0.8f, 0.0f, 0.8f)));
	tgGround->add(new Scale(glm::vec3(4.0f)));
	this->objects.push_back(new DrawableObject(sp, ground, tgGround));
}

//LAB 05 - TASK 3d - solar system scene prep
void Scene::galaxy() {
    Shader* vertexShader = new Shader();
    vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
    Shader* fragmentShader = new Shader();
    fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
    ShaderProgram* sp = new ShaderProgram(vertexShader, fragmentShader);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

    this->camera->registerObserver(sp);
    this->lights.at(0)->registerObserver(sp);

    Model* sun = new Model(sphere, size(sphere), 6);
    Model* earth = new Model(sphere, size(sphere), 6);
    Model* moon = new Model(sphere, size(sphere), 6);

    //------------------SUN--------------------------------------------
    TransformGroup* tgSun = new TransformGroup();
	tgSun->add(new Scale(glm::vec3(1.0f)));
    tgSun->add(new Spin(20.0f, glm::vec3(0, 1, 0)));

	//------------------EARTH------------------------------------------
	TransformGroup* tgEarth = new TransformGroup();
	tgEarth->add(new Scale(glm::vec3(0.5f)));//0.5

	//spin around itself
	tgEarth->add(new Spin(20.0f, glm::vec3(0, 1, 0)));

	//orbit around sun - 0,0,0
	tgEarth->add(new Translation(glm::vec3(4.0f, 0.0f, 0.0f))); //distance earth-sun
	tgEarth->add(new Spin(20.0f, glm::vec3(0, 1, 0)));

	//------------------MOON-------------------------------------------
	TransformGroup* tgMoon = new TransformGroup();
	tgMoon->add(new Scale(glm::vec3(0.1f)));

	//spin around itself
	tgMoon->add(new Spin(30.0f, glm::vec3(0, 1, 0)));
	tgMoon->add(new Translation(glm::vec3(2.0f, 0.0f, 0.0f))); //distance earth-moon

	//spin around earth
	tgMoon->add(new Spin(60.0f, glm::vec3(0, 1, 0)));
	tgMoon->add(tgEarth); //moon attached to eartch

    this->objects.push_back(new DrawableObject(sp, sun, tgSun));
	this->objects.push_back(new DrawableObject(sp, earth, tgEarth));
	this->objects.push_back(new DrawableObject(sp, moon, tgMoon));
}

void Scene::addObject(DrawableObject* drawObj) {
	this->objects.push_back(drawObj);
}

void Scene::draw() {

	//this->lights.at(0)->onChange();..onlyu 1 light
	for (auto l : this->lights) {
		l->onChange();
	}

	this->camera->onChange();

	//this->flashlight->lightPosition = this->camera->eye;
	//this->flashlight->lightDirecton = this->camera->target;
	//this->flashlight->onChange();

	// draw objects
	for (auto o : this->objects) {
		o->resetLightCounter();
		o->draw();
	}
}

void Scene::moveCam(int key) {
	this->camera->move(key);
}
