#include "game.h"

int main(void)
{
	game* gameVariable = new game();

	gameVariable->play();

	delete gameVariable;
}
