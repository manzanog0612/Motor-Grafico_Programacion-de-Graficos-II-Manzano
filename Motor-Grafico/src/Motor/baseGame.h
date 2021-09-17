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
		void play();
		virtual void update() = 0;


	private:
		bool init();
		void deinit();
		window* currentWindow;
		renderer* currentRenderer;
		bool windowExitEvent();
	};
}