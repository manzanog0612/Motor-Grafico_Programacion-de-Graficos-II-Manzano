#include "game.h"

game::game()
{

}

game::~game()
{

}

void game::draw()
{
	if(showingBoth)
	{
		quad->draw();
		triangle->draw();
	}
	else
	{
		activeShape->draw();
	}
}

void game::update()
{
	if(isKeyDown(ENGINE_KEY_ENTER))
	{
		flashingColorsScreen = !flashingColorsScreen;
	}

	if (isKeyDown(ENGINE_KEY_B))
	{
		showingBoth = !showingBoth;
		if(showingBoth)
		{
			if(activeShape == quad)
			{
				quad->setColor(1, 0, 0, 1);
				triangle->setColor(1, 1, 1, 1);
			}
			else
			{
				quad->setColor(1, 1, 1, 1);
				triangle->setColor(1, 0, 0, 1);
			}
		}
	}

	if (flashingColorsScreen)
	{
		float r = getRandomNumber(0, 1);
		float g = getRandomNumber(0, 1);
		float b = getRandomNumber(0, 1);
		changeClearColor(r, g, b, 1);
	}

	if (isKeyPressed(ENGINE_KEY_Q))
	{
		float rot = activeShape->getRotZ() - rotationSpeed * engine::time::getDeltaTime();
		activeShape->setRotZ(rot);
	}
	if (isKeyPressed(ENGINE_KEY_E))
	{
		float rot = activeShape->getRotZ() + rotationSpeed * engine::time::getDeltaTime();
		activeShape->setRotZ(rot);
	}

	if(isKeyDown(ENGINE_KEY_SPACE))
	{
		float r = getRandomNumber(0, 1);
		float g = getRandomNumber(0, 1);
		float b = getRandomNumber(0, 1);
		activeShape->setColor(r, g, b, 1);
	}
	if(isKeyPressed(ENGINE_KEY_LEFT) || isKeyPressed(ENGINE_KEY_A))
	{
		float posX = activeShape->getPosX();
		float posY = activeShape->getPosY();
		float posZ = activeShape->getPosZ();
		activeShape->setPos(posX + movementSpeed * engine::time::getDeltaTime(), posY, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_RIGHT) || isKeyPressed(ENGINE_KEY_D))
	{
		float posX = activeShape->getPosX();
		float posY = activeShape->getPosY();
		float posZ = activeShape->getPosZ();
		activeShape->setPos(posX - movementSpeed * engine::time::getDeltaTime(), posY, posZ);
	}
	if (isKeyPressed(ENGINE_KEY_UP) || isKeyPressed(ENGINE_KEY_W))
	{
		float posX = activeShape->getPosX();
		float posY = activeShape->getPosY();
		float posZ = activeShape->getPosZ();
		activeShape->setPos(posX, posY + movementSpeed * engine::time::getDeltaTime(), posZ);
	}
	if (isKeyPressed(ENGINE_KEY_DOWN) || isKeyPressed(ENGINE_KEY_S))
	{
		float posX = activeShape->getPosX();
		float posY = activeShape->getPosY();
		float posZ = activeShape->getPosZ();
		activeShape->setPos(posX, posY - movementSpeed * engine::time::getDeltaTime(), posZ);
	}
	if(isKeyPressed(ENGINE_KEY_X))
	{
		float posX = activeShape->getPosX();
		float posY = activeShape->getPosY();
		float posZ = activeShape->getPosZ();
		activeShape->setPos(posX, posY, posZ - movementSpeed * engine::time::getDeltaTime());
	}
	if(isKeyPressed(ENGINE_KEY_C))
	{
		float posX = activeShape->getPosX();
		float posY = activeShape->getPosY();
		float posZ = activeShape->getPosZ();
		activeShape->setPos(posX, posY, posZ + movementSpeed * engine::time::getDeltaTime());
	}

	if (isKeyDown(ENGINE_KEY_R))
	{
		activeShape->setScale(1, 1, 1);
	}
	if(isKeyDown(ENGINE_KEY_T))
	{
		activeShape->setScale(2, 2, 2);
	}
	if (isKeyDown(ENGINE_KEY_Y))
	{
		activeShape->setScale(8, 8, 8);
	}

	if(isKeyDown(ENGINE_KEY_1))
	{
		activeShape = triangle;
		if(showingBoth)
		{
			triangle->setColor(1, 0, 0 ,1);
			quad->setColor(1, 1, 1, 1);
		}
	}
	else if(isKeyDown(ENGINE_KEY_2))
	{
		activeShape = quad;
		if (showingBoth)
		{
			triangle->setColor(1, 1, 1, 1);
			quad->setColor(1, 0, 0, 1);
		}
	}
}

void game::init()
{
	quad = new engine::shape(4);
	quad->assingRenderer(currentRenderer);
	triangle = new engine::shape(3);
	triangle->assingRenderer(currentRenderer);
	movementSpeed = 10.f;
	rotationSpeed = 5.f;
	activeShape = triangle;
}

void game::deInit()
{
	delete quad;
	delete triangle;
}