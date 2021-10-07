#include "game.h"

game::game()
{
	sprite = nullptr;
	colors[0] = glm::vec4(1, 0, 0, 1);
	colors[1] = glm::vec4(0, 1, 0, 1);
	colors[2] = glm::vec4(0, 0, 1, 1);
	colors[3] = glm::vec4(1, 1, 1, 1);
	nextColor = colors[0];
	flickerSpeed = 2;
	float t = 0;
}

game::~game()
{

}

void game::draw()
{
	sprite->draw();
}

void game::update()
{
	t += engine::time::getDeltaTime() * flickerSpeed;
	if(t < 1)
	{
		sprite->setColor(lerp(sprite->getColor(), nextColor, t));
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
	}
}

void game::init()
{
	sprite = new engine::sprite(currentRenderer, "../Resources/Textures/stefanito.png");
	sprite->setScale(25, 25, 25);
}

void game::deInit()
{
	delete sprite;
}