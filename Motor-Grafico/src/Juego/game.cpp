#include "game.h"
#include <iostream>

game::game()
{
	sprite = nullptr;
	sprite2 = nullptr;
	colors[0] = glm::vec4(0, 0, 0, 1);
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
	sprite->draw();
	sprite2->draw();
}

void game::update()
{
	t += engine::time::getDeltaTime();
	if(t < timeBetweenChanges)
	{
		sprite->setColor(lerp(sprite->getColor(), nextColor, t));
		sprite2->setColor(lerp(sprite2->getColor(), nextColor2, t));
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
		float rot = sprite->getRotZ() - rotationSpeed * engine::time::getDeltaTime();
		sprite->setRotZ(rot);
	}
	if (isKeyPressed(ENGINE_KEY_E))
	{
		float rot = sprite->getRotZ() + rotationSpeed * engine::time::getDeltaTime();
		sprite->setRotZ(rot);
	}
	if(isKeyPressed(ENGINE_KEY_R))
	{
		float rot = sprite2->getRotY() + rotationSpeed * engine::time::getDeltaTime();
		sprite2->setRotY(rot);
	}
	if (isKeyPressed(ENGINE_KEY_T))
	{
		float rot = sprite2->getRotY() - rotationSpeed * engine::time::getDeltaTime();
		sprite2->setRotY(rot);
	}
}

void game::init()
{
	sprite = new engine::sprite(currentRenderer, "../Resources/Textures/stefanito.png");
	sprite->setScale(25, 25, 25);
	sprite2 = new engine::sprite(currentRenderer, "../Resources/Textures/Image Campus.png");
	sprite2->setScale(30, 20, 10);
	sprite2->setPos(0, -7.5f, -.1f);
	sprite2->invertX();
}

void game::deInit()
{
	delete sprite;
	delete sprite2;
}