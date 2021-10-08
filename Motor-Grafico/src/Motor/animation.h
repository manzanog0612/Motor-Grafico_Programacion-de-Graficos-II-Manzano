#pragma once
#include "exports.h"
#include <vector>

namespace engine
{
	class ENGINE_API animation
	{
	public:
		void play();
		void stop();
		void update();
		bool isPlaying();
		void repeatAnimation(bool active);
		void addAnimationFrame(unsigned int textureID);
		void removeAnimationFrame(unsigned int textureID);
		unsigned int getCurrentAnimationFrame();
	private:
		std::vector<unsigned int> animationFrames;
		int animationID = 0;
		int currentFrame = 0;
		float currentTime = 0;
		float timeBetweenFrames = .10f;
		bool repeat = true;
		bool playing = false;
	};
}