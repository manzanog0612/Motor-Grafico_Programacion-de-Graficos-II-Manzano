#include "game.h"
#include <iostream>
#include <sstream>
#include <string>

game::game()
{
	stefano = nullptr;
	imageCampus = nullptr;
	container = nullptr;
	awesomeface = nullptr;
	megaman = nullptr;
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
	megaman->draw();
	triangle->draw();
	triangle2->draw();
	triangle3->draw();
	quad->draw();
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

	if(isKeyPressed(ENGINE_KEY_A))
	{
		megaman->setRot(0, 0, 0);
		glm::vec3 pos = megaman->getPos();
		megaman->setPos(pos.x + engine::time::getDeltaTime() * megamanRunSpeed, pos.y, pos.z);
		megaman->playAnimation(megamanRunAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_D))
	{
		megaman->invertX();
		glm::vec3 pos = megaman->getPos();
		megaman->setPos(pos.x - engine::time::getDeltaTime() * megamanRunSpeed, pos.y, pos.z);
		megaman->playAnimation(megamanRunAnimationID);
	}
	else
	{
		megaman->stopAnimation(megamanRunAnimationID);
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

	if(megaman->getPos().x > 22)
	{
		glm::vec3 currentPos = megaman->getPos();
		megaman->setPos(-22, currentPos.y, currentPos.z);
	}
	else if (megaman->getPos().x < -22)
	{
		glm::vec3 currentPos = megaman->getPos();
		megaman->setPos(22, currentPos.y, currentPos.z);
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

	stefano = new engine::sprite(currentRenderer, "../res/assets/textures/stefanito.png");
	stefano->setScale(glm::vec3(10, 10, 10));
	
	imageCampus = new engine::sprite(currentRenderer, "../res/assets/textures/Image Campus.png");
	imageCampus->setScale(glm::vec3(30, 20, 10));
	imageCampus->setPos(glm::vec3(0, -9.f, -.1f));
	imageCampus->invertX();

	container = new engine::sprite(currentRenderer, "../res/assets/textures/container.jpg");
	container->setScale(glm::vec3(10, 10, 10));
	container->setPos(glm::vec3(-15, 0, 0));

	awesomeface = new engine::sprite(currentRenderer, "../res/assets/textures/awesomeface.png");
	awesomeface->setScale(glm::vec3(10, 10, 10));
	awesomeface->setPos(glm::vec3(15, 0, 0));

	std::ostringstream oss;
	const char* megamanPartialFilePath = "../res/assets/textures/Megaman Sprites/megaman";
	oss << megamanPartialFilePath << 0 << ".png";
	megaman = new engine::sprite(currentRenderer, oss.str().c_str());

	std::ostringstream oss2;
	oss2 << megamanPartialFilePath << 1 << ".png";
	megamanRunAnimationID = megaman->createAnimation(oss2.str().c_str());

	for (int i = 2; i < 11; i++)
	{
		std::ostringstream oss3;
		oss3 << megamanPartialFilePath << i << ".png";
		megaman->addFrameToAnimation(megamanRunAnimationID, oss3.str().c_str());
	}
	megaman->setAnimationSpeed(megamanRunAnimationID, megamanRunSpeed);
	megaman->setScale(5, 5, 5);
	megaman->setPos(0, 10, 0);

	changeClearColor(glm::vec4(.25, .25, .5, 1));
}

void game::deInit()
{
	delete cam;
	delete stefano;
	delete imageCampus;
	delete container;
	delete awesomeface;
	delete megaman;
	delete triangle;
	delete quad;
}