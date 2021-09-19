#pragma once
#include "exports.h"
#include <list>

namespace engine
{

	class window;

	class ENGINE_API input
	{
	public:
		input(window* window);
		~input();
		bool isKeyPressed(int keycode, window* window);
		bool isKeyDown(int keycode, window* window);
	private:
	};
}
