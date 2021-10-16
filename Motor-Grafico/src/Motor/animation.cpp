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
	}
	void animation::play()
	{
		playing = true;
	}
	void animation::stop()
	{
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
				currentFrame = 0;
				currentTime = 0;
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
	void animation::setAnimation(textureData* animationAtlasData, int columns, int rows)
	{
		texture = animationAtlasData;
		float spriteWidth = texture->width / columns;
		float spriteHeight = texture->height / rows;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				glm::vec2* newCoord = new glm::vec2[4];
				newCoord[0].x = (spriteWidth + (spriteWidth * j)) / texture->width;			// top right
				newCoord[0].y = (spriteHeight * i) / texture->height;						// top right
				newCoord[1].x = (spriteWidth + (spriteWidth * j)) / texture->width; 		// bottom right
				newCoord[1].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom right
				newCoord[2].x = (spriteWidth * j) / texture->width;							// bottom left
				newCoord[2].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom left
				newCoord[3].x = (spriteWidth * j) / texture->width;							// top left 
				newCoord[3].y = (spriteHeight * i) / texture->height;						// top left 
				textureCoordinates.push_back(newCoord);
			}
		}
	}
	void animation::setAnimation(textureData* animationAtlasData, atlasCutConfig config)
	{
		texture = animationAtlasData;
		float spriteWidth = 0;
		float spriteHeight = 0;
		if(config.useSize)
		{
			spriteWidth = config.spriteWidth;
			spriteHeight = config.spriteHeight;
		}
		else
		{
			spriteWidth = texture->width / config.columns;
			spriteHeight = texture->height / config.rows;
		}
		int framesCount = 0;
		int x = config.offsetX;
		for (int i = config.offsetY; i < config.rows; i++)
		{
			while(x < config.columns)
			{
				glm::vec2* newCoord = new glm::vec2[4];
				newCoord[0].x = (spriteWidth + (spriteWidth * x)) / texture->width;			// top right
				newCoord[0].y = (spriteHeight * i) / texture->height;						// top right
				newCoord[1].x = (spriteWidth + (spriteWidth * x)) / texture->width; 		// bottom right
				newCoord[1].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom right
				newCoord[2].x = (spriteWidth * x) / texture->width;							// bottom left
				newCoord[2].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom left
				newCoord[3].x = (spriteWidth * x) / texture->width;							// top left 
				newCoord[3].y = (spriteHeight * i) / texture->height;						// top left 
				textureCoordinates.push_back(newCoord);
				framesCount++;
				x++;
				if (framesCount == config.framesAmount) return;
			}
			x = 0;
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
