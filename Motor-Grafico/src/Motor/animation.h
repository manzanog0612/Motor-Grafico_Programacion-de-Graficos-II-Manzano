#pragma once
#include "exports.h"
#include <vector>

namespace engine
{
	class ENGINE_API animation
	{
	public:
		animation();
		~animation();
		void play();
		void stop();
		void update();
		bool isPlaying();
		void repeatAnimation(bool active);
		void addAnimationFrame(unsigned int textureID);
		void removeAnimationFrame(unsigned int textureID);
		void setAnimationSpeed(float speed);
		unsigned int getCurrentAnimationFrame();
	private:
		std::vector<unsigned int> animationFrames;
		int animationID = 0;
		int currentFrame = 0;
		float currentTime = 0;
		float timeBetweenFrames = 1.f;
		float animationSpeed = 1.f;
		bool repeat = false;
		bool playing = false;
	};
}