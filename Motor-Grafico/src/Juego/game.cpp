#include "game.h"

game::game()
{

}

game::~game()
{

}

void game::draw()
{

}

void game::update()
{
	if(isKeyDown(ENGINE_KEY_ENTER))
	{
		flashingColorsScreen = !flashingColorsScreen;
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

}

void game::deInit()
{

}