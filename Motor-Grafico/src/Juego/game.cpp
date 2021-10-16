#include "game.h"
#include <iostream>

game::game()
{
	stefano = nullptr;
	imageCampus = nullptr;
	container = nullptr;
	awesomeface = nullptr;
	archer = nullptr;
	triangle = nullptr;
	quad = nullptr;
	colors[0] = glm::vec4(0, 0, 0, 0);
	colors[1] = glm::vec4(1, 0, 0, 1);
	colors[2] = glm::vec4(0, 1, 0, 1);
	colors[3] = glm::vec4(0, 0, 1, 1);
	colors[4] = glm::vec4(1, 1, 0, 1);
	colors[5] = glm::vec4(0, 1, 1, 1);
	colors[6] = glm::vec4(1, 0, 1, 1);
	colors[7] = glm::vec4(1, 1, 1, 1);
	nextColor = colors[0];
	nextColor2 = colors[4];
	rotationSpeed = 2;
	timeBetweenChanges = 1;
	t = 0;
	currentColorIndex = 0;
	currentColorIndex2 = 5;
}

game::~game()
{

}

void game::draw()
{
	stefano->draw();
	imageCampus->draw();
	container->draw();
	awesomeface->draw();
	triangle->draw();
	triangle2->draw();
	triangle3->draw();
	quad->draw();
	archer->draw();
}

void game::update()
{
	t += engine::time::getDeltaTime();
	if(t < timeBetweenChanges)
	{
		stefano->setColor(lerp(stefano->getColor(), nextColor, t));
		imageCampus->setColor(lerp(imageCampus->getColor(), nextColor2, t));
	}
	else
	{
		t = 0;
		currentColorIndex++;
		if(currentColorIndex == colorsArraySize)
		{
			currentColorIndex = 0;
		}
		nextColor = colors[currentColorIndex];

		currentColorIndex2++;
		if (currentColorIndex2 == colorsArraySize)
		{
			currentColorIndex2 = 0;
		}
		nextColor2 = colors[currentColorIndex2];
	}
	if (isKeyPressed(ENGINE_KEY_Q))
	{
		float rot = stefano->getRot().z - rotationSpeed * engine::time::getDeltaTime();
		stefano->setRot(glm::vec3(0, 0, rot));
	}
	if (isKeyPressed(ENGINE_KEY_E))
	{
		float rot = stefano->getRot().z + rotationSpeed * engine::time::getDeltaTime();
		stefano->setRot(glm::vec3(0, 0, rot));
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
	}

	if(isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed / 2, pos.y + engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunUpLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed / 2, pos.y + engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunUpRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed / 2, pos.y - engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunDownLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed / 2, pos.y - engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunDownRightAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunLeftAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_D))
	{
		archer->invertX();
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed, pos.y, pos.z);
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
	}


	if(isKeyPressed(ENGINE_KEY_LEFT))
	{
		glm::vec3 movement = { engine::time::getDeltaTime() * cameraSpeed, 0, 0 };
		cam->moveCamera(movement);
	}
	if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		glm::vec3 movement = { engine::time::getDeltaTime() * -cameraSpeed, 0, 0 };
		cam->moveCamera(movement);
	}
	if (isKeyPressed(ENGINE_KEY_UP))
	{
		glm::vec3 movement = { 0, engine::time::getDeltaTime() * cameraSpeed , 0 };
		cam->moveCamera(movement);
	}
	if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		glm::vec3 movement = { 0, engine::time::getDeltaTime() * -cameraSpeed , 0 };
		cam->moveCamera(movement);
	}
}

void game::init()
{

	glm::vec3 camStartingPos = { 0, 0, -15 };
	glm::vec3 camLookPos = { 0, 0, 0 };
	glm::vec3 camUpVector = { 0, 1, 0 };
	cam = new engine::camera(currentRenderer, camStartingPos, camLookPos, camUpVector);

	triangle = new engine::shape(currentRenderer, 3);
	triangle->setScale(3, 3, 3);
	triangle->setPos(14, -10, 0);
	triangle->setColor(1, 1, 0, 1);

	triangle2 = new engine::shape(currentRenderer, 3);
	triangle2->setScale(3, 3, 3);
	triangle2->setPos(17, -10, 0);
	triangle2->setColor(1, 1, 0, 1);

	triangle3 = new engine::shape(currentRenderer, 3);
	triangle3->setScale(3, 3, 3);
	triangle3->setPos(15.5, -7, 0);
	triangle3->setColor(1, 1, 0, 1);

	quad = new engine::shape(currentRenderer, 4);
	quad->setScale(5, 5, 5);
	quad->setPos(-15, -10, 0);
	quad->setColor(0, 1, 1, 1);

	stefano = new engine::sprite(currentRenderer, "../res/assets/textures/stefanito.png", true);
	stefano->setScale(glm::vec3(10, 10, 10));
	
	imageCampus = new engine::sprite(currentRenderer, "../res/assets/textures/Image Campus.png", true);
	imageCampus->setScale(glm::vec3(30, 20, 10));
	imageCampus->setPos(glm::vec3(0, -9.f, -.1f));
	imageCampus->invertX();

	container = new engine::sprite(currentRenderer, "../res/assets/textures/container.jpg", true);
	container->setScale(glm::vec3(10, 10, 10));
	container->setPos(glm::vec3(-15, 0, 0));

	awesomeface = new engine::sprite(currentRenderer, "../res/assets/textures/awesomeface.png", true);
	awesomeface->setScale(glm::vec3(10, 10, 10));
	awesomeface->setPos(glm::vec3(15, 0, 0));

	archer = new engine::sprite(currentRenderer, "../res/assets/textures/Atlas Sprites/archerFullAtlas.png", false);

	archerAtlas = archer->createAnimationAtlas("../res/assets/textures/Atlas Sprites/archerFullAtlas.png", false);

	engine::atlasCutConfig archerRunAtlasConfig;

	archerRunAtlasConfig.CutByCount(10, 7, 6, 5, 8);
	archerRunLeftAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 0, 0, 8);
	archerRunRightAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 8, 0, 8);
	archerRunUpAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 2, 3, 8);
	archerRunDownAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 4, 2, 8);
	archerRunUpLeftAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 8, 4, 8);
	archerRunDownLeftAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 6, 1, 8);
	archerRunUpRightAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 0, 4, 8);
	archerRunDownRightAnimationID = archer->createAnimation(archerAtlas, archerRunAtlasConfig);

	archer->setAnimationSpeed(archerRunRightAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunLeftAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunUpAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunUpLeftAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunUpRightAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunDownAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunDownLeftAnimationID, runSpeed);
	archer->setAnimationSpeed(archerRunDownRightAnimationID, runSpeed);
	
	archer->setScale(5, 5, 5);
	archer->setPos(0, 10, 0);

	changeClearColor(glm::vec4(.25, .25, .5, 1));
}

void game::deInit()
{
	delete cam;
	delete stefano;
	delete imageCampus;
	delete container;
	delete awesomeface;
	archer->deleteAnimationAtlas(archerAtlas);
	delete archer;
	delete triangle;
	delete quad;
}