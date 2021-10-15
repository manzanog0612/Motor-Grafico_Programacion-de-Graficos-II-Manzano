#include "animation.h"
#include "time.h"
#include "glfw3.h"
#include "textureImporter.h"
#include <algorithm>

namespace engine
{
	animation::animation()
	{
		texture = nullptr;
	}
	animation::~animation()
	{
		for (int i = 0; i < textureCoordinates.size(); i++)
		{
			delete[] textureCoordinates[i];
		}
		delete texture;
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
	void animation::setAnimation(const char* AtlasFilepath, int columns, int rows)
	{
		texture = new textureData(textureImporter::loadTexture(AtlasFilepath));
		float spriteWidth = texture->width / columns;
		float spriteHeight = texture->height / rows;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				glm::vec2* newCoord = new glm::vec2[4];
				newCoord[0].x = (spriteWidth + (spriteWidth * j)) / texture->width; 		// bottom right
				newCoord[0].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom right
				newCoord[1].x = (spriteWidth + (spriteWidth * j)) / texture->width;			// top right
				newCoord[1].y = (spriteHeight * i) / texture->height;						// top right
				newCoord[2].x = (spriteWidth * j) / texture->width;							// top left 
				newCoord[2].y = (spriteHeight * i) / texture->height;						// top left 
				newCoord[3].x = (spriteWidth * j) / texture->width;							// bottom left
				newCoord[3].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom left
				textureCoordinates.push_back(newCoord);
			}
		}
	}
	unsigned int animation::getTextureID()
	{
		return texture->ID;
	}
	glm::vec2* animation::getCurrentFramesCoordinates()
	{
		return textureCoordinates[currentFrame];
	}
}
