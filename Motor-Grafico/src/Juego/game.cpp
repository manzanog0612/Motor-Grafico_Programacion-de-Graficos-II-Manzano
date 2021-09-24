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

	if (flashingColorsScreen)
	{
		float r = getRandomNumber(0, 1);
		float g = getRandomNumber(0, 1);
		float b = getRandomNumber(0, 1);
		changeClearColor(r, g, b, 1);
	}

	static float rot = 0;
	if (isKeyPressed(ENGINE_KEY_Q))
	{
		rot += .1f;
		quad->setRotZ(rot);
	}
	if (isKeyPressed(ENGINE_KEY_E))
	{
		rot -= .1f;
		quad->setRotZ(rot);
	}

	if(isKeyDown(ENGINE_KEY_SPACE))
	{
		float r = getRandomNumber(0, 1);
		float g = getRandomNumber(0, 1);
		float b = getRandomNumber(0, 1);
		quad->setColor(r, g, b, 1);
	}
	if(isKeyPressed(ENGINE_KEY_LEFT) || isKeyPressed(ENGINE_KEY_A))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX - movementSpeed * engine::time::getDeltaTime(), posY, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_RIGHT) || isKeyPressed(ENGINE_KEY_D))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX + movementSpeed * engine::time::getDeltaTime(), posY, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_UP) || isKeyPressed(ENGINE_KEY_W))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX, posY + movementSpeed * engine::time::getDeltaTime(), posZ);
	}
	if (isKeyPressed(ENGINE_KEY_DOWN) || isKeyPressed(ENGINE_KEY_S))
	{
		float posX = quad->getPosX();
		float posY = quad->getPosY();
		float posZ = quad->getPosZ();
		quad->setPos(posX, posY - movementSpeed * engine::time::getDeltaTime(), posZ);
	}
	if (isKeyDown(ENGINE_KEY_R))
	{
		quad->setScale(1, 1, 1);
	}
	if(isKeyDown(ENGINE_KEY_T))
	{
		quad->setScale(2, 2, 2);
	}
	if (isKeyDown(ENGINE_KEY_Y))
	{
		quad->setScale(4, 4, 4);
	}
}

void game::init()
{
	quad = new engine::shape(3);
	quad->assingRenderer(currentRenderer);
	movementSpeed = 2.f;
}

void game::deInit()
{

}