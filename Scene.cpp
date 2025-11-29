#include "Scene.h"

Scene::Scene() {
	this->camera = new Camera();

	//white light middle...[0]
	this->lights.push_back(new Light(
		glm::vec3(0.0, 0.0, 0.0), //pos
		glm::vec4(1.0, 1.0, 1.0, 1.0), //diff col
		glm::vec4(1.0, 1.0, 1.0, 1.0), //spec col
		1.0f, 0.0f, 0.0f)); //light attenuation

	//white light...[1]
	this->lights.push_back(new Light(
		glm::vec3(-10.0, 10.0, 0.0),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f, 0.0f, 0.0f));

	//main light for forest scene...moon high above teh scene ...[2]
	this->lights.push_back(new Light(
		glm::vec3(0.0f, 20.0f, 0.0f),
		glm::vec4(0.8f, 0.8f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
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
	this->lights.at(2)->registerObserver(spGrow);

	this->growableTreeModel = new DrawableObject(
		spGrow,
		new Model(tree, size(tree), 6, "tree"),
		new TransformationComposite()
	);
	srand(time(0));

	//moved as general sp for all moles so it wouldnt be compiled each time we spawn a new mole but we use only this one
	this->spNewMoles = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	ShaderProgManager::registerAllObservers(this->spNewMoles, this->camera, this->flashlight);
	this->lights.at(2)->registerObserver(this->spNewMoles);
	this->spNewMoles->setUniform("useTexture", 1);


	ShaderProgram* spSkybox = ShaderProgManager::getShaderProgram(SKYBOX_VERTEX_SHADER, SKYBOX_FRAGMENT_SHADER);
	this->camera->registerObserver(spSkybox);

	this->skybox = (new DrawableObject(
		spSkybox,
		ModelManger::getModel("cube.obj"),
		new TransformationComposite(),
		new Texture()
	));

	this->bezierFollowerObject = new DrawableObject(
		this->spNewMoles,
		ModelManger::getModel("formula1.obj"),
		nullptr,
		TextureManager::getTexture("fiona.png")
	);
}

void Scene::tryoutScene() {
	this->sceneType = "tryoutScene";
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	this->flashlight->registerObserver(sp);
	this->lights.at(0)->registerObserver(sp);
	this->camera->registerObserver(sp);

	sp->setUniform("objectColor", glm::vec4(1, 0, 0, 1.0));
	sp->setUniform("lightPosition", this->lights.at(1)->lightPosition); //for Lambert shader

	//so that if a tree is grown inside of a scene with specific lights it has those light as well
	this->lights.at(0)->registerObserver(this->growableTreeModel->shaderProgram); 
	
	//FOR TESTING PURPOSES
	sp->setUniform("camPosition", this->camera->eye);
	sp->setUniform("shinines", 32.0f);
	sp->setUniform("specularColor", this->lights.at(1)->specularColor);
	ShaderProgManager::registerAllObservers(sp, this->camera, this->lights.at(1));
	//this->camera->registerObserver(sp);
	//this->lights.at(0)->registerObserver(sp);

	Model* m4 = ModelManger::getModel("new_sphere.obj");

	Texture* t3 = TextureManager::getTexture("grass.png");
	Texture* t2 = TextureManager::getTexture("wooden_fence.png");
	Texture* t4 = TextureManager::getTexture("sun.png");


	ShaderProgram* sp2 = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	sp2->setUniform("useTexture", 1);
	ShaderProgManager::registerAllObservers(sp2, this->camera, this->lights.at(1));
	//this->camera->registerObserver(sp2);
	//this->lights.at(0)->registerObserver(sp2);

	TransformationComposite* tg4 = new TransformationComposite();

	TransformationComposite* tg5 = new TransformationComposite();
	tg5->add(new WCustomTransform(20.0f));
	tg5->add(new Translation(glm::vec3(-2.0f, 0.0f, 0.0f)));


	//this->addObject(new DrawableObject(sp, m4, tg4));
	this->addObject(new DrawableObject(sp2, m4, tg5, t4));
	this->addObject(new DrawableObject(sp2, m4, tg4));
}

void Scene::testScene() {
	this->sceneType = "testScene";
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));
	//sp->setUniform("objectColor", glm::vec4(1.0, 0.0, 0.0, 1.0));

	this->camera->registerObserver(sp);
	this->lights.at(1)->registerObserver(sp); //white on up right
	//this->lights.at(13)->registerObserver(sp); //ambient green
	//this->lights.at(14)->registerObserver(sp); //directional blue
	//this->flashlight->registerObserver(sp);

	ShaderProgram* spTexture = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	this->camera->registerObserver(spTexture);
	this->lights.at(1)->registerObserver(spTexture);


	Model* m = new Model(sphere, size(sphere), 6, "sphere");
	Model* m2 = ModelManger::getModel("new_sphere.obj"); Texture* t = TextureManager::getTexture("wooden_fence.png");

	TransformationComposite* tg1 = new TransformationComposite();
	tg1->add(new Translation(glm::vec3(2.0, 0.0, 0.0)));
	tg1->add(new Scale(glm::vec3(0.1f)));

	TransformationComposite* tg2 = new TransformationComposite();
	tg2->add(new Translation(glm::vec3(-2.0, 0.0, 0.0)));
	tg2->add(new Scale(glm::vec3(0.1f)));

	TransformationComposite* tg3 = new TransformationComposite();
	tg3->add(new Translation(glm::vec3(0.0f, 2.0f, 0.0)));
	tg3->add(new Scale(glm::vec3(0.1f)));

	TransformationComposite* tg4 = new TransformationComposite();
	tg4->add(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	tg4->add(new Scale(glm::vec3(0.1f)));

	sp->setUniform("useTexture", 0);
	this->objects.push_back(new DrawableObject(sp, m, tg1));
	this->objects.push_back(new DrawableObject(sp, m, tg2));
	this->objects.push_back(new DrawableObject(sp, m, tg3));
	
	spTexture->setUniform("useTexture", 1);
	this->objects.push_back(new DrawableObject(spTexture, m2, tg4, t)); //textured one
}

//LAB 05 - TASK 3a - simple static triangle
void Scene::basicScene() {
	this->sceneType = "basicScene";
	/*Shader* vertexShader = new Shader();
	vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader* fragmentShader = new Shader();
	//fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, CONSTANT_FRAGMENT_SHADER);...for basic triangle
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);*/
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	//sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	TransformationComposite* tgM = new TransformationComposite();
	tgM->add(new Scale(glm::vec3(0.2f)));

	TransformationComposite* tgZPG = new TransformationComposite();
	tgZPG->add(new Translation(glm::vec3(0.0f, -4.0f, -1.0f)));
	tgZPG->add(new Scale(glm::vec3(0.2f)));
	tgZPG->add(new Rotation(45.0f, glm::vec3(1.0, 1.0, 0.0)));

	TransformationComposite* tgLogin = new TransformationComposite();
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
	this->sceneType = "symetricalSpheres";
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, BLINN_FRAGMENT_SHADER);
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));

	this->camera->registerObserver(sp);
	//this->lights.at(0)->registerObserver(sp);
	for (auto l : lights) {
		l->registerObserver(sp);
	}

	Model* m = new Model(sphere, size(sphere), 6, "sphere");

	TransformationComposite* tg1 = new TransformationComposite();
	tg1->add(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	tg1->add(new Scale(glm::vec3(0.1f)));

	TransformationComposite* tg2 = new TransformationComposite();
	tg2->add(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	tg2->add(new Scale(glm::vec3(0.1f)));

	TransformationComposite* tg3 = new TransformationComposite();
	tg3->add(new Translation(glm::vec3(0.0f, 0.0f, 2.0f)));
	tg3->add(new Scale(glm::vec3(0.1f)));

	TransformationComposite* tg4 = new TransformationComposite();
	tg4->add(new Translation(glm::vec3(0.0f, 0.0f, -2.0f)));
	tg4->add(new Scale(glm::vec3(0.1f)));

	this->objects.push_back(new DrawableObject(sp, m, tg1));
	this->objects.push_back(new DrawableObject(sp, m, tg2));
	this->objects.push_back(new DrawableObject(sp, m, tg3));
	this->objects.push_back(new DrawableObject(sp, m, tg4));
}

//LAB 05 - TASK 3c - forest with bushes and ground
void Scene::forestScene() {
	this->sceneType = "forest";
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER); //PHONG CORRECT
	sp->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));
	//sp->setUniform("objectColor", glm::vec4(1.0, 0.0, 0.0, 1.0));

	this->growableTreeModel->shaderProgram = sp;

	this->camera->registerObserver(sp);

	this->lights.at(2)->registerObserver(sp); //moon/sun
	//this->lights.at(13)->registerObserver(sp); //ambient light for testing
	for (int i = 3; i < 13; i++) { //fireflies
		this->lights.at(i)->registerObserver(sp);
	}
	//this->lights.at(15)->registerObserver(sp); //flashlight
	this->flashlight->registerObserver(sp);


	Model* treeModel = new Model(tree, size(tree), 6, "tree");
	Model* bushModel = new Model(bushes, size(bushes), 6, "bush");
	Model* firefly = new Model(sphere, size(sphere), 6, "sphere");

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
		TransformationComposite* tgTree = new TransformationComposite();
		tgTree->add(new Translation(glm::vec3(xTreeOffset, yTreeBushOffset, zTreeOffset)));
		tgTree->add(new Scale(glm::vec3(0.1f)));
		this->objects.push_back(
			new DrawableObject(
				sp, treeModel, tgTree
			)
		);

		//50 bushes objects
		TransformationComposite* tgBush = new TransformationComposite();
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

		TransformationComposite* tgFirefly = new TransformationComposite();
		tgFirefly->add(new Scale(glm::vec3(0.008f))); // make it bigger
		//tgFirefly->add(new Translation(pl->lightPosition));
		tgFirefly->add(new Translation(this->lights.at(i)->lightPosition));
		//tgFirefly->add(new RandTranslateDynamic(this->lights.at(i)->lightPosition, maxDist));

		this->objects.push_back(new DrawableObject(spFirefly, firefly, tgFirefly));
	}

	//------------------TERAIN------------------------------------------
	/*Shader* f = new Shader();
	f->createShaderFromFile(GL_FRAGMENT_SHADER, TEXTURE_FRAGMENT_SHADER);*/
	ShaderProgram* fsdfaa = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	fsdfaa->setUniform("useTexture", 1);

	this->camera->registerObserver(fsdfaa); //need to register so shader would "act upon" all lights
	this->flashlight->registerObserver(fsdfaa);
	this->lights.at(2)->registerObserver(fsdfaa); //moon/sun
	for (int i = 3; i < 13; i++) { //fireflies
		this->lights.at(i)->registerObserver(fsdfaa);
	}
	this->flashlight->registerObserver(fsdfaa);

	Model* ground = ModelManger::getModel("teren.obj"); Texture* grassText = TextureManager::getTexture("grass.png");
	TransformationComposite* tgGround = new TransformationComposite();
	tgGround->add(new Translation(glm::vec3(30.0f, 0.0f, 30.0f)));
	tgGround->add(new Scale(glm::vec3(0.08f)));

	this->addObject(new DrawableObject(fsdfaa, ground, tgGround, grassText));
	//------------------BACKGROUDN------------------------------------------

	Model* skyDome = ModelManger::getModel("skydome.obj");
	Texture* textureSky = TextureManager::getTexture("skydome.png");
	TransformationComposite* tgSky = new TransformationComposite();
	tgSky->add(new Translation(glm::vec3(0.0f, 0.0f, 4.0f)));
	tgSky->add(new Scale(glm::vec3(2.0f)));
	
	this->addObject(new DrawableObject(fsdfaa, skyDome, tgSky, textureSky));
	//------------------SHROCK+FIONA------------------------------------------
	Model* shrek = ModelManger::getModel("shrek.obj");
	Model* fiona = ModelManger::getModel("fiona.obj");

	Texture* texShrek = TextureManager::getTexture("shrek.png");
	Texture* texFiona = TextureManager::getTexture("fiona.png");

	TransformationComposite* tgShrek = new TransformationComposite();
	tgShrek->add(new Scale(glm::vec3(0.2f)));
	tgShrek->add(new Translation(glm::vec3(3.0f, 0.0f, 3.0f)));

	TransformationComposite* tgFiona = new TransformationComposite();
	tgFiona->add(new Scale(glm::vec3(0.2f)));
	tgFiona->add(new Rotation(-45.0f, glm::vec3(0.0, 1.0, 0.0)));
	tgFiona->add(new Translation(glm::vec3(3.2f, 0.0f, 3.2f)));

	this->addObject(new DrawableObject(fsdfaa, shrek, tgShrek, texShrek));
	this->addObject(new DrawableObject(fsdfaa, fiona, tgFiona, texFiona));
}

//LAB 05 - TASK 3d - solar system scene
void Scene::galaxy() {
	this->sceneType = "galaxy";
    /*Shader* vertexShader = new Shader();
    vertexShader->createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER);
    Shader* fragmentShader = new Shader();
    //fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, PHONG_CORRECT_FRAGMENT_SHADER);
	fragmentShader->createShaderFromFile(GL_FRAGMENT_SHADER, TEXTURE_FRAGMENT_SHADER);*/
	ShaderProgram* spSun = ShaderProgManager::getShaderProgram(VERTEX_SHADER, TEXTURE_FRAGMENT_SHADER);
	spSun->setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));
    this->camera->registerObserver(spSun);
    this->lights.at(0)->registerObserver(spSun);

	ShaderProgram* spPlanets = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	spPlanets->setUniform("useTexture", 1);
	this->camera->registerObserver(spPlanets);
	this->lights.at(0)->registerObserver(spPlanets);
	this->lights.at(2)->registerObserver(spPlanets);

    //Model* sun = new Model(sphere, size(sphere), 6);
	Model* planet = ModelManger::getModel("new_sphere.obj");
	Texture* sunTex = TextureManager::getTexture("sun.png");
	Texture* earthTex = TextureManager::getTexture("earth.png");
	Texture* moonTex = TextureManager::getTexture("moon.png");
	Texture* venuTex = TextureManager::getTexture("venus.png");
	Texture* mercTex = TextureManager::getTexture("mercury.png");
	Texture* starsTex = TextureManager::getTexture("stars.png");

    //------------------SUN--------------------------------------------
	TransformationComposite* tgSun = new TransformationComposite();
	tgSun->add(new Scale(glm::vec3(1.0f)));
    tgSun->add(new Spin(2.0f, glm::vec3(0, 1, 0)));
	//------------------MERCURY------------------------------------------
	TransformationComposite* tgMercury = new TransformationComposite();
	tgMercury->add(new Scale(glm::vec3(0.2f)));
	tgMercury->add(new Spin(20.0f, glm::vec3(0, 1, 0)));

	//orbit around sun - 0,0,0
	tgMercury->add(new Translation(glm::vec3(2.0f, 0.0f, 0.0f))); //distance venus-sun
	tgMercury->add(new Spin(40.0f, glm::vec3(0, 1, 0)));
	//------------------VENUS------------------------------------------
	TransformationComposite* tgVenus = new TransformationComposite();
	tgVenus->add(new Scale(glm::vec3(0.4f)));
	tgVenus->add(new Spin(1000.0f, glm::vec3(0, 1, 0)));

	//orbit around sun - 0,0,0
	tgVenus->add(new Translation(glm::vec3(4.0f, 0.0f, 0.0f))); //distance venus-sun
	tgVenus->add(new Spin(30.0f, glm::vec3(0, 1, 0)));
	//------------------EARTH------------------------------------------
	TransformationComposite* tgEarth = new TransformationComposite();
	tgEarth->add(new Scale(glm::vec3(0.5f)));//0.5

	//spin around itself
	tgEarth->add(new Spin(30.0f, glm::vec3(0, 1, 0)));

	//orbit around sun - 0,0,0
	tgEarth->add(new Translation(glm::vec3(6.0f, 0.0f, 0.0f))); //distance earth-sun
	tgEarth->add(new Spin(20.0f, glm::vec3(0, 1, 0)));
	//------------------MOON-------------------------------------------
	TransformationComposite* tgMoon = new TransformationComposite();
	tgMoon->add(new Scale(glm::vec3(0.1f)));

	//spin around itself
	tgMoon->add(new Spin(20.0f, glm::vec3(0, 1, 0)));
	tgMoon->add(new Translation(glm::vec3(2.0f, 0.0f, 0.0f))); //distance earth-moon

	//spin around earth
	tgMoon->add(new Spin(60.0f, glm::vec3(0, 1, 0)));
	tgMoon->add(tgEarth); //moon attached to eartch
	//------------------BACKGROUND-------------------------------------------
	TransformationComposite* tgBack = new TransformationComposite();
	tgBack->add(new Scale(glm::vec3(10.0f)));

    this->objects.push_back(new DrawableObject(spSun, planet, tgSun, sunTex));
	this->objects.push_back(new DrawableObject(spPlanets, planet, tgEarth, earthTex));
	this->objects.push_back(new DrawableObject(spPlanets, planet, tgMoon, moonTex));
	this->objects.push_back(new DrawableObject(spPlanets, planet, tgVenus, venuTex));
	this->objects.push_back(new DrawableObject(spPlanets, planet, tgMercury, mercTex));
	this->objects.push_back(new DrawableObject(spSun, planet, tgBack, starsTex));
}

void Scene::whacAMole() {
	this->sceneType = "whacamole";
	ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	ShaderProgManager::registerAllObservers(sp, this->camera, this->flashlight);
	this->lights.at(2)->registerObserver(sp);//2

	sp->setUniform("useTexture", 1);
	//------------------GROUND------------------------------------------
	this->camera->registerObserver(sp);
	Model* ground = ModelManger::getModel("teren.obj"); Texture* grassText = TextureManager::getTexture("grass.png");
	TransformationComposite* tgGround = new TransformationComposite();
	tgGround->add(new Scale(glm::vec3(0.08f)));
	this->addObject(new DrawableObject(sp, ground, tgGround, grassText));
	//------------------BACKGROUDN------------------------------------------
	Model* skyDome = ModelManger::getModel("skydome.obj"); Texture* textureSky = TextureManager::getTexture("skydome.png");
	TransformationComposite* tgSky = new TransformationComposite();
	tgSky->add(new Scale(glm::vec3(2.0f)));
	this->addObject(new DrawableObject(sp, skyDome, tgSky, textureSky));
	//------------------RANDOM FREDDY CASUAL SPEED +1 score--------------
	Model* freddy = ModelManger::getModel("meme_glamrock_freddy.obj"); Texture* freddyTex = TextureManager::getTexture("TEX_GlamRockFreddy_BaseColor.png");

	//intervals so that the obj is on the flat part of the UNSCALED terrain:
	//x (-3.5, 2.5)...z(-3.0, 3.5)
	float maxX = 2.5f; float minX = -3.5f;
	float maxZ = 3.5f; float minZ = -3.0f;

	for (int i = 0; i < 10; i++) {
		TransformationComposite* tgFreddy = new TransformationComposite();
		tgFreddy->add(new Scale(glm::vec3(0.5f)));
		tgFreddy->add(new RandMovement(1.0f, glm::vec3(minX, 0.0f, minZ), glm::vec3(maxX, 0.0f, maxZ)));
		this->addObject(new DrawableObject(sp, freddy, tgFreddy, freddyTex));
	}

	//------------------RANDOM SHREK SUPER SPEED +5 score------------------
	Model* shrek = ModelManger::getModel("shrek.obj"); Texture* shrekTex = TextureManager::getTexture("shrek.png");

	for (int i = 0; i < 5; i++) {
		TransformationComposite* tgShrek = new TransformationComposite();
		tgShrek->add(new Scale(glm::vec3(0.2f)));
		tgShrek->add(new RandMovement(3.0f, glm::vec3(minX, 0.0f, minZ), glm::vec3(maxX, 0.0f, maxZ)));
		this->addObject(new DrawableObject(sp, shrek, tgShrek, shrekTex));
	}
	//------------------RANDOM TITLE SUPER SPEED +99 score------------------
	Model* title = ModelManger::getModel("ZPG Title.obj"); Texture* titleTex = TextureManager::getTexture("wooden_fence.png");
	for (int i = 0; i < 3; i++) {
		TransformationComposite* tgTitle = new TransformationComposite();
		tgTitle->add(new Rotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
		tgTitle->add(new Scale(glm::vec3(0.1f)));
		tgTitle->add(new RandMovement(1.0f, glm::vec3(minX, 0.1f, minZ), glm::vec3(maxX, 1.5f, maxZ)));
		this->addObject(new DrawableObject(sp, title, tgTitle, titleTex));
	}
	//------------------SMALL RAND FOREST------------------------------------------
	Model* tree = ModelManger::getModel("tree.obj");
	Texture* treeTex = TextureManager::getTexture("bake_tree.png");

	float xTreeOffset = 0.0f;
	float zTreeOffset = 0.0f;

	/*for (int i = 0; i < 7; i++) {
		TransformationComposite* jjj = new TransformationComposite();
		xTreeOffset = -4.0 + (float)(rand()) / RAND_MAX * (4.0 - (-4.0));
		zTreeOffset = -4.0 + (float)(rand()) / RAND_MAX * (4.0 - (-4.0));
		jjj->add(new Scale(glm::vec3(1.5f)));
		jjj->add(new Translation(glm::vec3(xTreeOffset, 0.0, zTreeOffset)));
		this->addObject(new DrawableObject(sp, tree, jjj, treeTex));
	}*/

	//Model* fiona = ModelManger::getModel("fiona.obj");
	//Texture* ggg = TextureManager::getTexture("fiona.png");
	//TransformationComposite* jjj = new TransformationComposite();
	//jjj->add(new Rotation(180.0, glm::vec3(0.0, 1.0, 0.0)));
	//jjj->add(new Scale(glm::vec3(0.5)));
	//jjj->add(new BezierSimple(
	//	glm::vec3(-2.77, 0.00, 0.08),
	//	glm::vec3(-3.05, 0.00, -1.79),
	//	glm::vec3(-1.17, 0.00, -2.93),
	//	glm::vec3(0.31, 0.00, -2.01),
	//	0.1f));

	//vector<glm::vec3> points = {
	//	glm::vec3(-4.37, 0.11, 0.45), glm::vec3(-3.92,  0.06, -1.40), glm::vec3(-1.65, -0.00, -1.64), glm::vec3(-0.97, -0.00, 0.34), //S1
	//	glm::vec3(0.68, -0.00, 2.93), glm::vec3(2.11, -0.00, 3.07), glm::vec3(2.81, 0.04, 1.02) //S2
	//};
	//jjj->add(new BezierSpline(points, 0.5f));

	//this->objects.push_back(new DrawableObject(sp, fiona, jjj, ggg));
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

	//spawning new mole in whac a mole scene
	if (this->sceneType == "whacamole") {
		if (this->objects.size() < 10 + 2) {
			//this->objects.clear(); //FOR TESTING
			int r = rand() % 100;
			int modelType;
			if (r < 60) { //60% chance for freddy spawn
				modelType = 1;
			}
			else if (r < 90) {//30% for shrek
				modelType = 2;
			}
			else {//10% for title
				modelType = 3;
			}
			spawnNewMole(modelType);
		}
	}

	if (this->bezierPointsComplete) { //all bezier points were selected
		this->bezierFollowerObject->transformation = new TransformationComposite();
		this->bezierFollowerObject->transformation->add(new Scale(vec3(0.01f)));
		this->bezierFollowerObject->transformation->add(new Rotation(90.0f, vec3(0.0, 1.0, 0.0)));
		this->bezierFollowerObject->transformation->add(new BezierSpline(this->bezierPoints, 0.5f));
		this->objects.push_back(this->bezierFollowerObject);
		this->bezierPoints.clear();
		this->bezierPointsComplete = false;
	}

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
			if (name != "plain" && name != "skydome" && name != "teren" && name != "tree") {
				//o->visible = false;
				this->objects.erase(remove(this->objects.begin(), this->objects.end(), o), this->objects.end());// removing by the object
				//printf("removing object: %s\n", o->model->modelName.c_str());

				if (this->sceneType == "whacamole") {
					if (o->model->modelName == "meme_glamrock_freddy.obj") {
						this->score++;
						printf("\t\t\t\t\t\tYOU WHACKED freddy \t [Common] +1 point \tScore: %d\n", this->score);
					}
					else if (o->model->modelName == "shrek.obj") {
						this->score += 5;
						printf("\t\t\t\t\t\tYOU WHACKED shrek \t [Rare] +5 points \tScore: %d\n", this->score);
					}
					else if (o->model->modelName == "ZPG Title.obj") {
						this->score += 99;
						printf("\t\t\t\t\t\tYOU WHACKED zpg title \t [Mythic] +99 points \tScore: %d\n", this->score);
					}
				}
			} else {
				printf("cannot remove object: %s\n", o->model->modelName.c_str());
			}
		}
	}
}

void Scene::growNewTree(glm::vec3 position) {
	TransformationComposite* tg = new TransformationComposite();
	tg->add(new Scale(glm::vec3(0.2f)));
	tg->add(new Translation(position));

	DrawableObject* newTree = new DrawableObject(this->growableTreeModel->shaderProgram, this->growableTreeModel->model, tg);
	this->addObject(newTree);
	//printf("planting tree at: %f,%f,%f\n", position.x, position.y, position.z);
}

void Scene::spawnNewMole(int type) {
	//ShaderProgram* sp = ShaderProgManager::getShaderProgram(VERTEX_SHADER, MULTI_FRAGMENT_SHADER);
	//ShaderProgManager::registerAllObservers(sp, this->camera, this->flashlight);
	//this->lights.at(2)->registerObserver(sp);//2

	//sp->setUniform("useTexture", 1);

	float maxX = 2.5f; float minX = -3.5f;
	float maxZ = 3.5f; float minZ = -3.0f;

	Model* m;
	TransformationComposite* tg = new TransformationComposite();
	Texture* t;

	switch (type) {
		case 1: //freddy
			m = ModelManger::getModel("meme_glamrock_freddy.obj");
			t = TextureManager::getTexture("TEX_GlamRockFreddy_BaseColor.png");
			tg->add(new Scale(glm::vec3(0.5f)));
			tg->add(new RandMovement(1.0f, glm::vec3(minX, 0.0f, minZ), glm::vec3(maxX, 0.0f, maxZ)));
			break;
		case 2: //shrek
			m = ModelManger::getModel("shrek.obj");
			t = TextureManager::getTexture("shrek.png");
			tg->add(new Scale(glm::vec3(0.2f)));
			tg->add(new RandMovement(3.0f, glm::vec3(minX, 0.0f, minZ), glm::vec3(maxX, 0.0f, maxZ)));
			break;
		case 3: //title
			m = ModelManger::getModel("ZPG Title.obj");
			t = TextureManager::getTexture("wooden_fence.png");
			tg->add(new Rotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
			tg->add(new Scale(glm::vec3(0.1f)));
			tg->add(new RandMovement(1.0f, glm::vec3(minX, 0.1f, minZ), glm::vec3(maxX, 1.5f, maxZ)));
			break;
		default: //freddy
			m = ModelManger::getModel("meme_glamrock_freddy.obj");
			t = TextureManager::getTexture("TEX_GlamRockFreddy_BaseColor.png");
			tg->add(new Scale(glm::vec3(0.5f)));
			tg->add(new RandMovement(1.0f, glm::vec3(minX, 0.0f, minZ), glm::vec3(maxX, 0.0f, maxZ)));
			break;
	}
	this->addObject(new DrawableObject(this->spNewMoles, m, tg, t));
}

void Scene::printAllBezierPoints() {
	printf("POINTS FOR BEZIER: \n");
	for (int i = 0; i < this->bezierPoints.size(); i++) {
		glm::vec3 point = this->bezierPoints.at(i);
		printf("%d \t\t[%.2f\t%.2f\t%.2f]\n", i, point.x, point.y, point.z);
	}
}

void Scene::cropBezierPoints() {
	if (bezierPoints.size() < 4) {
		bezierPoints.clear();
		return;
	}


	int n = this->bezierPoints.size();
	int toRemove = (n - 1) % 3; //points as 4,3,3,3 etc

	if (toRemove != 0) { //throw away unnecesary
		this->bezierPoints.resize(n - toRemove);
	}
	this->bezierPointsComplete = true;
}

void Scene::drawSkybox() {
	glDepthFunc(GL_LEQUAL);

	this->skybox->draw();

	glDepthFunc(GL_LESS);
}