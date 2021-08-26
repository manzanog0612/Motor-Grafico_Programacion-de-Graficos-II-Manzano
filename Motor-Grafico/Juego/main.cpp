#include "game.h"

int main(void)
{
	game* gameVariable = new game();
	gameVariable->init();

	while(!gameVariable->windowExitEvent())
	{
		gameVariable->update();
	}

	gameVariable->deinit();
	delete gameVariable;
}
