#pragma once
#include "exports.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace engine
{

	struct texture;

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
		void setAnimationSpeed(float speed);
		void setAnimation(const char* AtlasFilepath, int rows, int columns);
		unsigned int getTextureID();
		glm::vec4 getCurrentFramesCoordinates();
	private:
		std::vector<glm::vec4*> textureCoordinates;
		texture* tex;
		int currentFrame = 0;
		float currentTime = 0;
		float timeBetweenFrames = 1.f;
		float animationSpeed = 1.f;
		bool repeat = false;
		bool playing = false;
	};
}