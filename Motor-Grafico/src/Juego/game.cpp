#include "game.h"
#include <iostream>

game::game()
{
	//imageCampus = nullptr;

	for (short i = 0; i < 6; i++)
	{
		container[i] = nullptr;
	}

	lightBox = nullptr;
	conteiner2 = nullptr;
	floor = nullptr;
	pointLight = nullptr;
	cubePearl = nullptr;
	cubeEmerald = nullptr;

	//archer = nullptr;
	//triangle = nullptr;
	//triangle2 = nullptr;
	//triangle3 = nullptr;
	//quad = nullptr;
	actualCam = nullptr;
	//tileMap = nullptr;
	colors[0] = glm::vec4(0, 0, 0, 0);
	colors[1] = glm::vec4(1, 0, 0, 1);
	colors[2] = glm::vec4(0, 1, 0, 1);
	colors[3] = glm::vec4(0, 0, 1, 1);
	colors[4] = glm::vec4(1, 1, 0, 1);
	colors[5] = glm::vec4(0, 1, 1, 1);
	colors[6] = glm::vec4(1, 0, 1, 1);
	colors[7] = glm::vec4(1, 1, 1, 1);
	nextColor = colors[4];
	rotationSpeed = 2;
	timeBetweenChanges = 1;
	t = 0;
	currentColorIndex = 5;

	//archerRunLeftAnimationID = 0;
	//archerRunRightAnimationID = 0;
	//archerRunUpAnimationID = 0;
	//archerRunUpLeftAnimationID = 0;
	//archerRunUpRightAnimationID = 0;
	//archerRunDownAnimationID = 0;
	//archerRunDownLeftAnimationID = 0;
	//archerRunDownRightAnimationID = 0;
}

game::~game()
{

}

void game::draw()
{
	//tileMap->draw();
	//imageCampus->draw();

	lightBox->draw();

	//for (short i = 0; i < 6; i++)
	//{
	//	container[i]->draw();
	//}
	//awesomeface->draw();
	floor->draw();

	cubeEmerald->draw();
	cubePearl->draw();
	cubeBronze->draw();
	cubeGold->draw();
	cubeCyanPlastic->draw();
	cubeRedPlastic->draw();
	cubeGreenRubber->draw();
	cubeYellowRubber->draw();
	conteiner2->draw();

	pointLight->draw();

	
	//triangle->draw();
	//triangle2->draw();
	//triangle3->draw();
	//quad->draw();
	
	//archer->draw();
}

void game::update()
{
	/*t += engine::time::getDeltaTime();
	if(t < timeBetweenChanges)
	{
		imageCampus->setColor(lerp(imageCampus->getColor(), nextColor, t));
	}
	else
	{
		t = 0;
	
		currentColorIndex++;
		if (currentColorIndex == colorsArraySize)
		{
			currentColorIndex = 0;
		}
		nextColor = colors[currentColorIndex];
	}
	if(isKeyPressed(ENGINE_KEY_R))
	{
		float rot = imageCampus->getRot().y + rotationSpeed * engine::time::getDeltaTime();
		imageCampus->setRot(glm::vec3(0, rot, 0));
	}
	if (isKeyPressed(ENGINE_KEY_T))
	{
		float rot = imageCampus->getRot().y - rotationSpeed * engine::time::getDeltaTime();
		imageCampus->setRot(glm::vec3(0, rot, 0));
	}*/

	/*if (isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed / 2, pos.y + engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunUpLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed / 2, pos.y + engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunUpRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed / 2, pos.y - engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunDownLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed / 2, pos.y - engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunDownRightAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunLeftAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x, pos.y + engine::time::getDeltaTime() * runSpeed, pos.z);
		archer->playAnimation(archerRunUpAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x, pos.y - engine::time::getDeltaTime() * runSpeed, pos.z);
		archer->playAnimation(archerRunDownAnimationID);
	}
	else
	{
		archer->stopAllAnimations();
	}*/

	/*if (isKeyPressed(ENGINE_KEY_LEFT))
	{
		glm::vec3 movement = { engine::time::getDeltaTime() * -cameraSpeed, 0, 0 };
		cam->moveCamera(movement);
	}
	else if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		glm::vec3 movement = { engine::time::getDeltaTime() * cameraSpeed, 0, 0 };
		cam->moveCamera(movement);
	}
	if (isKeyPressed(ENGINE_KEY_UP))
	{
		glm::vec3 movement = { 0, engine::time::getDeltaTime() * cameraSpeed , 0 };
		cam->moveCamera(movement);
	}
	else if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		glm::vec3 movement = { 0, engine::time::getDeltaTime() * -cameraSpeed , 0 };
		cam->moveCamera(movement);
	}
	else if (isKeyPressed(ENGINE_KEY_U))
	{
		glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * cameraSpeed };
		cam->moveCamera(movement);
	}
	else if (isKeyPressed(ENGINE_KEY_I))
	{
		
		glm::vec3 movement = { 0, 0, engine::time::getDeltaTime() * -cameraSpeed };
		cam->moveCamera(movement);
	}*/

	//box movement

	glm::vec3 movement = glm::vec3(0, 0, 0);
	glm::vec3 front = glm::normalize(actualCam->getFront() - actualCam->getPos());
	glm::vec3 up = glm::normalize(actualCam->getUp());
	float boxSpeed = 1;
	float boxFaces = 6;

	front.y = 0;

	if (isKeyPressed(ENGINE_KEY_UP))
	{
		movement += front * boxSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		movement -= front * boxSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_LEFT))
	{
		movement -= glm::normalize(glm::cross(front, up));
	}
	else if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		movement += glm::normalize(glm::cross(front, up));
	}

	if (isKeyPressed(ENGINE_KEY_Q))
	{
		movement += up * boxSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_E))
	{
		movement -= up * boxSpeed;
	}
	//cubeShape->setPos(cubeShape->getPos() + movement);
	lightBox->setPos(lightBox->getPos() + movement);

	//for (short i = 0; i < boxFaces; i++)
	//{
	//	container[i]->setPos(container[i]->getPos() + movement);
	//}
	//
	//awesomeface->setPos(awesomeface->getPos() + movement);

	boxPos += movement;

	//camera movement

	float cameraMovementAmount = engine::time::getDeltaTime() * cameraSpeed;

	if (isKeyPressed(ENGINE_KEY_W))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::FRONT);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::BACK);
	}

	if (isKeyPressed(ENGINE_KEY_D))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::RIGHT);
	}
	else if (isKeyPressed(ENGINE_KEY_A))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::LEFT);
	}

	actualCam->rotateCamera(getMouseOffset());

	if (actualCam == thirdPersonCam)
	{
		thirdPersonCam->updateTargetPos(conteiner2->getPos());
	}

	pointLight->setPos(lightBox->getPos());
	std::cout << "x: " << front.x << " - y: " << front.y << " - z: " << front.z << std::endl;
	//if (isKeyDown(ENGINE_KEY_ENTER))
	//{
	//	if (cam->getCameraType() == engine::MOVEMENT_TYPE::FPS)
	//	{
	//		cam->setCameraType(engine::MOVEMENT_TYPE::THIRD_PERSON);
	//	}
	//	else
	//	{
	//		cam->setCameraType(engine::MOVEMENT_TYPE::FPS);
	//	}
	//}
		
	/* 
	
	PARA METER ROTACIÒN DE CAMARA PROXIMAMENTE

	if (isKeyPressed(ENGINE_KEY_K))
	{
		glm::vec3 rotation = { 0, 0, engine::time::getDeltaTime() * cameraSpeed };
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		glm::vec3 rotation = { 0, 0, engine::time::getDeltaTime() * -cameraSpeed };
	}
	
	*/

	/*if (isKeyDown(ENGINE_KEY_ENTER))
	{
		if (hasCollider(archer)) removeCollider(archer);
		else addCollider(archer, false);
	}*/

	//updateCollisions(tileMap);
}

void game::init()
{
	glm::vec3 camPos = { 0, 30, 10 };
	glm::vec3 camView = { 0, -1, 0 };
	glm::vec3 camUp = { 0, 1, 0 };
	//renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType
	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = thirdPersonCam;
	//tileMap = new engine::tileMap(currentRenderer);

	/*if (tileMap->importTileMap("../res/assets/tilemapreal.tmx"))
	{
		std::cout << "tilemap loaded";
	}
	else
	{
		std::cout << "tilemap failed to load";
	}*/

	/*triangle = new engine::shape(currentRenderer, 3);
	triangle->setScale(3, 3, 3);
	triangle->setPos(-14, -10, 0);
	triangle->setColor(1, 1, 0, 1);

	triangle2 = new engine::shape(currentRenderer, 3);
	triangle2->setScale(3, 3, 3);
	triangle2->setPos(-17, -10, 0);
	triangle2->setColor(1, 1, 0, 1);

	triangle3 = new engine::shape(currentRenderer, 3);
	triangle3->setScale(3, 3, 3);
	triangle3->setPos(-15.5, -7, 0);
	triangle3->setColor(1, 1, 0, 1);

	quad = new engine::shape(currentRenderer, 4);
	quad->setScale(5, 5, 5);
	quad->setPos(15, -10, 0);
	quad->setColor(0, 1, 1, 1);

	imageCampus = new engine::sprite(currentRenderer, "../res/assets/textures/Image Campus.png", true);
	imageCampus->setScale(glm::vec3(30, 20, 10));
	imageCampus->setPos(glm::vec3(0, -9.f, -.1f));

	container = new engine::sprite(currentRenderer, "../res/assets/textures/container.jpg", true);
	container->setScale(glm::vec3(10, 10, 10));
	container->setPos(glm::vec3(-15, 0, 0));*/

	conteiner2 = new engine::sprite(currentRenderer, "../res/assets/textures/container2.png", "../res/assets/textures/container2_specular.png", true, engine::MATERIAL::PEARL);
	conteiner2->setPos(glm::vec3(0, 7.5f, 10));
	conteiner2->setScale(glm::vec3(10, 10, 10));
	conteiner2->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));

	

	lightBox = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::PEARL);
	lightBox->setPos(glm::vec3(0, 40, 20));
	lightBox->setScale(glm::vec3(5, 5, 5));

	pointLight = new engine::light(currentRenderer);
	pointLight->setColor(glm::vec4(1, 1, 1, 1));

	cubeEmerald = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::EMERALD);
	cubeEmerald->setPos(glm::vec3(-30, 15, 0));
	cubeEmerald->setScale(glm::vec3(10, 10, 10));
	cubePearl = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::PEARL);
	cubePearl->setPos(glm::vec3(-10, 15, 0));
	cubePearl->setScale(glm::vec3(10, 10, 10));
	cubeBronze = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::BRONZE);
	cubeBronze->setPos(glm::vec3(10, 15, 0));
	cubeBronze->setScale(glm::vec3(10, 10, 10));
	cubeGold = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::GOLD);
	cubeGold->setPos(glm::vec3(30, 15, 0));
	cubeGold->setScale(glm::vec3(10, 10, 10));
	cubeCyanPlastic = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::CYAN_PLASTIC);
	cubeCyanPlastic->setPos(glm::vec3(-30, 0, 0));
	cubeCyanPlastic->setScale(glm::vec3(10, 10, 10));
	cubeRedPlastic = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::RED_PLASTIC);
	cubeRedPlastic->setPos(glm::vec3(-10, 0, 0));
	cubeRedPlastic->setScale(glm::vec3(10, 10, 10));
	cubeGreenRubber = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::GREEN_RUBBER);
	cubeGreenRubber->setPos(glm::vec3(10, 0, 0));
	cubeGreenRubber->setScale(glm::vec3(10, 10, 10));
	cubeYellowRubber = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::YELLOW_RUBBER);
	cubeYellowRubber->setPos(glm::vec3(30, 0, 0));
	cubeYellowRubber->setScale(glm::vec3(10, 10, 10));

	floor = new engine::sprite(currentRenderer, "../res/assets/textures/papa.png", "../res/assets/textures/papa.png", true, engine::MATERIAL::YELLOW_RUBBER);
	floor->setScale(glm::vec3(500, 500, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0,-5,0));

	/*archer = new engine::sprite(currentRenderer, "../res/assets/textures/Atlas Sprites/archerFullAtlas.png", false);
	
	engine::atlasCutConfig archerRunAtlasConfig;

	archerRunAtlasConfig.CutByCount(10, 7, 6, 5, 8);
	archerRunLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 0, 0, 8);
	archerRunRightAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 8, 0, 8);
	archerRunUpAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 2, 3, 8);
	archerRunDownAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 4, 2, 8);
	archerRunUpLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 8, 4, 8);
	archerRunDownLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 6, 1, 8);
	archerRunUpRightAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 0, 4, 8);
	archerRunDownRightAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archer->setAnimationFullTime(archerRunRightAnimationID, .5f);
	archer->setAnimationFullTime(archerRunLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpRightAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownRightAnimationID, .5f);

	archer->setScale(32, 32, 1);
	archer->setPos(-80, 20, 0);*/

	changeClearColor(glm::vec4(0.5f, 0.5f, 1, 1));
	//changeClearColor(glm::vec4(.25, .25, .5, 1));
	//addCollider(archer, false);
	//addCollider(awesomeface, false);
	//addCollider(triangle, false);
	//addCollider(triangle2, false);
	//addCollider(triangle3, false);
	//addCollider(quad, true);
	//addCollider(container, true);
}

void game::deInit()
{
	delete cubeEmerald;
	delete cubePearl;
	delete cubeBronze;
	delete cubeGold;
	delete cubeCyanPlastic;
	delete cubeRedPlastic;
	delete cubeGreenRubber;
	delete cubeYellowRubber;

	delete firstPersonCam;
	delete thirdPersonCam;

	delete lightBox;

	conteiner2->deinit();
	delete conteiner2;

	floor->deinit();
	delete floor;

	

	//archer->deinit();
	//delete archer;
	//delete triangle;
	//delete triangle2;
	//delete triangle3;
	//delete quad;
}