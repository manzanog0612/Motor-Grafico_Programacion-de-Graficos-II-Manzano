#pragma once
#include "window.h"

namespace engine
{

#ifdef BASEGAME_EXPORTS
#define BASEGAME_API __declspec(dllexport)
#else
#define BASEGAME_API __declspec(dllimport)
#endif

	class baseGame
	{
	public:
		baseGame();
		~baseGame();
		BASEGAME_API bool init();
		BASEGAME_API void update();
		BASEGAME_API void deinit();
		BASEGAME_API bool windowExitEvent();

	private:
		window* currentWindow;
		bool windowShouldClose;
	};

}