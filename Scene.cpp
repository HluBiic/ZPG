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


	this->flashlight = new Light(// ...SPOTLIGHT
		glm::vec3(0.0f, 2.0f, 2.0f),
		glm::vec3(0.0f, -1.0f, -1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		15.0f,
		1.0f, 0.09f, 0.032f
	);

	ShaderProgram* spGrow = ShaderProgManager::getShaderProgram(VERTEX_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	spGrow->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));
	this->camera->registerObserver(spGrow);
	this->flashlight->registerObserver(spGrow);

	this->growableTreeModel = new DrawableObject(
		spGrow,
		new Model(tree, size(tree), 6),
		new TransformGroup()
	);
	srand(time(0));
}

void Scene::tryoutScene() {
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, BLINN_FRAGMENT_SHADER);
	sp->setUniform("objectColor", glm::vec4(1, 0, 0, 1.0));
	sp->setUniform("lightPosition", this->lights.at(0)->lightPosition); //for Lambert shader
	//FOR TESTING PURPOSES
	sp->setUniform("camPosition", this->camera->eye);
	sp->setUniform("shinines", 32.0f);
	sp->setUniform("specularColor", this->lights.at(0)->specularColor);
	ShaderProgManager::registerAllObservers(sp, this->camera, this->lights.at(0));
	//this->camera->registerObserver(sp);
	//this->lights.at(0)->registerObserver(sp);

	Model* m4 = ModelManger::getModel("sphere.obj");

	Texture* t3 = TextureManager::getTexture("grass.png");
	Texture* t2 = TextureManager::getTexture("wooden_fence.png");
	Texture* t4 = TextureManager::getTexture("sun.png");


	ShaderProgram* sp2 = ShaderProgManager::getShaderProgram(VERTEX_SHADER, TEXTURE_FRAGMENT_SHADER);

	ShaderProgManager::registerAllObservers(sp2, this->camera, this->lights.at(0));
	//this->camera->registerObserver(sp2);
	//this->lights.at(0)->registerObserver(sp2);

	TransformGroup* tg4 = new TransformGroup();

	TransformGroup* tg5 = new TransformGroup();
	tg5->add(new Translation(glm::vec3(0.0f, 0.0f, -2.0f)));

	this->addObject(new DrawableObject(sp, m4, tg4));
	this->addObject(new DrawableObject(sp, m4, tg5));

}

//LAB 05 - TASK 3a - simple static triangle
void Scene::basicScene() {
	/*Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShader = new Shader();
	//fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, CONSTANT_FRAGMENT_SHADER);...for basic triangle
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);*/
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	//sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

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
	//Model* m = new Model("house.obj");
	Model* m = ModelManger::getModel("house.obj");
	Model* m2 = ModelManger::getModel("Login.obj");
	Model* m3 = ModelManger::getModel("ZPG Title.obj");

	this->objects.push_back(new DrawableObject(sp, m, tgM));
	this->objects.push_back(new DrawableObject(sp, m3, tgZPG));
	this->objects.push_back(new DrawableObject(sp, m2, tgLogin));
}

//LAB 05 - TASK 3b - 4x spheres symetricaly placed along axes
void Scene::symetricalSpheresScene() {
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, BLINN_FRAGMENT_SHADER);
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
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, CONSTANT_FRAGMENT_SHADER);
	ShaderProgram* sp2 = ShaderProgManager::getShaderProgram(VERTEX_SHADER, LAMBERT_FRAGMENT_SHADER);
	ShaderProgram* sp3 = ShaderProgManager::getShaderProgram(VERTEX_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	ShaderProgram* sp4 = ShaderProgManager::getShaderProgram(VERTEX_SHADER, BLINN_FRAGMENT_SHADER);

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
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	this->growableTreeModel->shaderProgram = sp;

	this->camera->registerObserver(sp);

	this->lights.at(2)->registerObserver(sp); //moon/sun
	for (int i = 3; i < 13; i++) { //fireflies
		this->lights.at(i)->registerObserver(sp);
	}
	//this->lights.at(15)->registerObserver(sp); //flashlight
	this->flashlight->registerObserver(sp);


	Model* treeModel = new Model(tree, size(tree), 6);
	Model* bushModel = new Model(bushes, size(bushes), 6);
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

	//------------------FIREFLIES------------------------------------------
	//sphere for fireflies...constant shader of white color
	/*Shader* fragmentShaderFirefly = new Shader();
	fragmentShaderFirefly->createShaderFromFile(GL_FRAGMENT_SHADER, CONSTANT_FRAGMENT_SHADER);*/
	ShaderProgram* spFirefly = ShaderProgManager::getShaderProgram(VERTEX_SHADER, CONSTANT_FRAGMENT_SHADER);

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

	//------------------GROUND------------------------------------------
	/*Shader* f = new Shader();
	f->createShaderFromFile(GL_FRAGMENT_SHADER, TEXTURE_FRAGMENT_SHADER);*/
	ShaderProgram* fsdfaa = ShaderProgManager::getShaderProgram(VERTEX_SHADER, TEXTURE_FRAGMENT_SHADER);

	this->camera->registerObserver(fsdfaa);

	Model* ground = ModelManger::getModel("teren.obj"); Texture* grassText = TextureManager::getTexture("grass.png");
	TransformGroup* tgGround = new TransformGroup();
	tgGround->add(new Translation(glm::vec3(30.0f, 0.0f, 30.0f)));
	tgGround->add(new Scale(glm::vec3(0.08f)));

	this->addObject(new DrawableObject(fsdfaa, ground, tgGround, grassText));

	//------------------BACKGROUDN------------------------------------------

	Model* skyDome = ModelManger::getModel("skydome.obj");
	Texture* textureSky = TextureManager::getTexture("skydome.png");
	TransformGroup* tgSky = new TransformGroup();
	tgSky->add(new Translation(glm::vec3(0.0f, 0.0f, 4.0f)));
	tgSky->add(new Scale(glm::vec3(2.0f)));
	
	this->addObject(new DrawableObject(fsdfaa, skyDome, tgSky, textureSky));
	//------------------SHROCK+FIONA------------------------------------------
	Model* shrek = ModelManger::getModel("shrek.obj");
	Model* fiona = ModelManger::getModel("fiona.obj");

	Texture* texShrek = TextureManager::getTexture("shrek.png");
	Texture* texFiona = TextureManager::getTexture("fiona.png");

	TransformGroup* tgShrek = new TransformGroup();
	tgShrek->add(new Scale(glm::vec3(0.2f)));
	tgShrek->add(new Translation(glm::vec3(3.0f, 0.0f, 3.0f)));

	TransformGroup* tgFiona = new TransformGroup();
	tgFiona->add(new Scale(glm::vec3(0.2f)));
	tgFiona->add(new Rotation(-45.0f, glm::vec3(0.0, 1.0, 0.0)));
	tgFiona->add(new Translation(glm::vec3(3.2f, 0.0f, 3.2f)));

	this->addObject(new DrawableObject(fsdfaa, shrek, tgShrek, texShrek));
	this->addObject(new DrawableObject(fsdfaa, fiona, tgFiona, texFiona));
}

//LAB 05 - TASK 3d - solar system scene prep
void Scene::galaxy() {
    /*Shader* vertexShader = new Shader();
    vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
    Shader* fragmentShader = new Shader();
    //fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, TEXTURE_FRAGMENT_SHADER);*/
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, TEXTURE_FRAGMENT_SHADER);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

    this->camera->registerObserver(sp);
    this->lights.at(0)->registerObserver(sp);

    //Model* sun = new Model(sphere, size(sphere), 6);
	Model* sun = ModelManger::getModel("sphere.obj");
	Texture* sunTex = TextureManager::getTexture("sun.png");
    //Model* earth = new Model(sphere, size(sphere), 6);
	Model* earth = ModelManger::getModel("sphere.obj");
	Texture* earthTex = TextureManager::getTexture("earth.png");
    //Model* moon = new Model(sphere, size(sphere), 6);
	Model* moon = ModelManger::getModel("sphere.obj");
	Texture* moonTex = TextureManager::getTexture("moon.png");

    //------------------SUN--------------------------------------------
    TransformGroup* tgSun = new TransformGroup();
	tgSun->add(new Scale(glm::vec3(1.0f)));
    tgSun->add(new Spin(10.0f, glm::vec3(0, 1, 0)));

	//------------------EARTH------------------------------------------
	TransformGroup* tgEarth = new TransformGroup();
	tgEarth->add(new Scale(glm::vec3(0.5f)));//0.5

	//spin around itself
	tgEarth->add(new Spin(30.0f, glm::vec3(0, 1, 0)));

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

    this->objects.push_back(new DrawableObject(sp, sun, tgSun, sunTex));
	this->objects.push_back(new DrawableObject(sp, earth, tgEarth, earthTex));
	this->objects.push_back(new DrawableObject(sp, moon, tgMoon, moonTex));
}

void Scene::whacAMole() {
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, TEXTURE_FRAGMENT_SHADER);
	ShaderProgManager::registerAllObservers(sp, this->camera, this->flashlight);
	//------------------GROUND------------------------------------------
	this->camera->registerObserver(sp);
	Model* ground = ModelManger::getModel("teren.obj"); Texture* grassText = TextureManager::getTexture("grass.png");
	TransformGroup* tgGround = new TransformGroup();
	tgGround->add(new Scale(glm::vec3(0.08f)));
	this->addObject(new DrawableObject(sp, ground, tgGround, grassText));
	//------------------BACKGROUDN------------------------------------------
	Model* skyDome = ModelManger::getModel("skydome.obj"); Texture* textureSky = TextureManager::getTexture("skydome.png");
	TransformGroup* tgSky = new TransformGroup();
	tgSky->add(new Scale(glm::vec3(2.0f)));
	this->addObject(new DrawableObject(sp, skyDome, tgSky, textureSky));
	//------------------10 RANDOM-------------------------------------------
	Model* freddy = ModelManger::getModel("meme_glamrock_freddy.obj"); Texture* freddyTex = TextureManager::getTexture("TEX_GlamRockFreddy_BaseColor.png");

	//intervals so that the obj is on the flat part of the UNSCALED terrain:
	//x (-3.5, 2.5)...z(-3.0, 3.5)
	float maxX = 2.5f; float minX = -3.5f;
	float maxZ = 3.5f; float minZ = -3.0f;

	for (int i = 0; i < 15; i++) {
		TransformGroup* tgFreddy = new TransformGroup();
		tgFreddy->add(new Scale(glm::vec3(0.5f)));
		tgFreddy->add(new RandMovement(1.0f, glm::vec3(minX, 0.0f, minZ), glm::vec3(maxX, 0.0f, maxZ)));
		this->addObject(new DrawableObject(sp, freddy, tgFreddy, freddyTex));
	}
}

void Scene::addObject(DrawableObject* drawObj) {
	this->objects.push_back(drawObj);
}

void Scene::draw() {
	//updating so that the cam "holds" the flashlight
	this->flashlight->lightPosition = this->camera->eye;
	this->flashlight->lightDirecton = this->camera->target;
	this->flashlight->onChange();

	//this->lights.at(0)->onChange();..onlyu 1 light
	for (auto l : this->lights) {
		l->onChange();
	}

	this->camera->onChange();

	// draw objects
	for (auto o : this->objects) {
		if (o->visible) {
			o->resetLightCounter();
			glStencilFunc(GL_ALWAYS, o->getID(), 0xFF);
			o->draw();
		}
	}
}

void Scene::moveCam(int key) {
	this->camera->move(key);
}

void Scene::setInactiveDrawObj(int id) {
	for (auto o : this->objects) {
		int objId = o->getID();
		if (objId == id) {
			string name = o->getModelName();
			if (name != "plain" && name != "skydome" && name != "teren") {
				//o->visible = false;
				this->objects.erase(remove(this->objects.begin(), this->objects.end(), o), this->objects.end());// removing by the object
				printf("removing object: %s\n", o->model->modelName.c_str());
			} else {
				printf("cannot remove object: %s\n", o->model->modelName.c_str());
			}
		}
	}
}

void Scene::growNewTree(glm::vec3 position) {
	TransformGroup* tg = new TransformGroup();
	tg->add(new Scale(glm::vec3(0.1f)));
	tg->add(new Translation(position));

	DrawableObject* newTree = new DrawableObject(this->growableTreeModel->shaderProgram, this->growableTreeModel->model, tg);
	this->addObject(newTree);
	printf("planting tree at: %f,%f,%f\n", position.x, position.y, position.z);
}

