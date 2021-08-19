#include "baseGame.h"

int main(void)
{
	engine::baseGame* gameEngine = new engine::baseGame();
	gameEngine->init();

	while (!gameEngine->windowExitEvent())
	{
		gameEngine->update();
	}

	gameEngine->deinit();
	delete gameEngine;
}