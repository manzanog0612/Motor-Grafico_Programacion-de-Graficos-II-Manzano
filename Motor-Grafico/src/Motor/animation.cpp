#include "animation.h"
#include "time.h"
#include <algorithm>
#include "glfw3.h"

namespace engine
{
	animation::animation()
	{

	}
	animation::~animation()
	{
		for(int i = 0; i < animationFrames.size(); i++)
		{
			glDeleteTextures(1, &animationFrames[i]);
		}
	}
	void animation::play()
	{
		currentFrame = 0;
		playing = true;
	}
	void animation::stop()
	{
		currentFrame = 0;
		playing = false;
	}
	void animation::update()
	{
		currentTime += time::getDeltaTime() * animationSpeed;
		if(currentTime > timeBetweenFrames)
		{
			currentTime = 0;
			currentFrame++;
			if(currentFrame == animationFrames.size())
			{
				if(repeat)
				{
					play();
				}
				else
				{
					stop();
				}
			}
		}
	}
	bool animation::isPlaying()
	{
		return playing;
	}
	void animation::repeatAnimation(bool active)
	{
		repeat = active;
	}
	void animation::addAnimationFrame(unsigned int textureID)
	{
		animationFrames.push_back(textureID);
	}
	void animation::removeAnimationFrame(unsigned int textureID)
	{
		animationFrames.erase(std::remove(animationFrames.begin(), animationFrames.end(), textureID), animationFrames.end());
	}
	unsigned int animation::getCurrentAnimationFrame()
	{
		return animationFrames[currentFrame];
	}
	void animation::setAnimationSpeed(float speed)
	{
		animationSpeed = speed;
	}
}
