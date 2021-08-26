#pragma once
#include "exports.h"
#include "window.h"
#include "renderer.h"

namespace engine
{

	class ENGINE_API baseGame
	{
	public:
		baseGame();
		~baseGame();
		bool init();
		void update();
		void deinit();
		bool windowExitEvent();

	private:
		window* currentWindow;
		renderer* currentRenderer;
		bool windowShouldClose;
	};

}