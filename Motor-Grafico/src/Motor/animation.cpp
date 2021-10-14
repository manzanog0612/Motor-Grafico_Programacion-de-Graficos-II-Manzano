#include "animation.h"
#include "time.h"
#include "glfw3.h"
#include "textureImporter.h"
#include <algorithm>

namespace engine
{
	animation::animation()
	{

	}
	animation::~animation()
	{

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
			if(currentFrame == textureCoordinates.size())
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
	void animation::setAnimationSpeed(float speed)
	{
		animationSpeed = speed;
	}
	void animation::setAnimation(const char* AtlasFilepath, int rows, int columns)
	{
		tex = new texture(textureImporter::loadTexture(AtlasFilepath));
	}
	unsigned int animation::getTextureID()
	{
		return tex->ID;
	}
	glm::vec4 animation::getCurrentFramesCoordinates()
	{
		return *textureCoordinates[currentFrame];
	}
}
