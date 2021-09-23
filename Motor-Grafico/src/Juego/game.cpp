#include "game.h"

game::game()
{

}

game::~game()
{

}

void game::draw()
{
	quad->draw();
}

void game::update()
{
	if(isKeyDown(ENGINE_KEY_ENTER))
	{
		flashingColorsScreen = !flashingColorsScreen;
	}

	if (isKeyPressed(ENGINE_KEY_SPACE))
	{
		static float z = 0;
		z += .1f;
		float r = getRandomNumber(0, 1);
		float g = getRandomNumber(0, 1);
		float b = getRandomNumber(0, 1);
		quad->setColor(r, g, b, 1);
		quad->setRotZ(z);
	}
	if(isKeyPressed(ENGINE_KEY_LEFT))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX - movementSpeed, posY, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX + movementSpeed, posY, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_UP))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX, posY + movementSpeed, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX, posY - movementSpeed, posZ);
	}

	if(flashingColorsScreen)
	{
		float r = getRandomNumber(0, 1);
		float g = getRandomNumber(0, 1);
		float b = getRandomNumber(0, 1);
		changeClearColor(r, g, b, 1);
	}
}

void game::init()
{
	quad = new engine::shape(4);
	quad->assingRenderer(currentRenderer);
	movementSpeed = 0.01f;
}

void game::deInit()
{

}