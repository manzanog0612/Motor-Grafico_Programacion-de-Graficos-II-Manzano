#pragma once
#include "exports.h"
#include "keycodes.h"
#include "time.h"

#include "shape.h"
#include "sprite.h"
#include "camera.h"

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
		// ~ ENGINE ~ Initializes the engine loops, being init(), update(), draw(), deInit(). 
		void play(int windowSizeX, int windowSizeY, const char* windowName);

		virtual void update() = 0;

		virtual void draw() = 0;

		virtual void init() = 0;

		virtual void deInit() = 0;

		// Input
		// ~ ENGINE ~  Returns true every frame the engine key is pressed. 
		bool isKeyPressed(int keycode);
		// ~ ENGINE ~  Returns true the first frame the engine key is down. 
		bool isKeyDown(int keycode);

		// General
		// ~ ENGINE ~  Changes screen clear color to the parameter float values. 
		void changeClearColor(glm::vec4 color);
		// ~ ENGINE ~  Returns a double corresponding to the current time since GLFW context started. 
		double getCurrentTime();

		// Lerp
		// ~ ENGINE ~  Lerps between two float values based on a t Value. 
		float lerp(float v0, float v1, float t);
		// ~ ENGINE ~  Lerps between two color values based on a t Value. 
		glm::vec4 lerp(glm::vec4 color1, glm::vec4 color2, float t);

		// Random
		// ~ ENGINE ~  Returns a random float between the minimun and the maximun value. 
		float getRandomNumber(float min, float max);
		// ~ ENGINE ~  Returns a random color value. 
		glm::vec4 getRandomColor();

	protected:
		renderer* currentRenderer;
	private:
		bool init_Internal(int windowSizeX, int windowSizeY, const char* windowName);
		void deinit_Internal();
		window* currentWindow;
		input* currentInput;
		time* currentTimer;
		bool windowExitEvent();
	};
}