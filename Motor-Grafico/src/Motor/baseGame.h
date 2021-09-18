#pragma once
#include "exports.h"

namespace engine
{

	class window;
	class renderer;
	class input;

	class ENGINE_API baseGame
	{
	public:
		baseGame();
		~baseGame();
		void play();
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void init() = 0;
		virtual void deInit() = 0;
		
		//input
		bool isKeyPressed(int keycode);
		bool isKeyDown(int keycode);

	private:
		bool init_Internal();
		void deinit_Internal();
		window* currentWindow;
		renderer* currentRenderer;
		input* currentInput;
		bool windowExitEvent();
	};
}