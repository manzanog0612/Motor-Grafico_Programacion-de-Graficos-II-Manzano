#pragma once
#include "exports.h"
#include "entity2D.h"
#include <vector>

namespace engine
{

	class animation;

	class ENGINE_API sprite : public entity2D
	{
	public:
		sprite(renderer* render, const char* filePathImage);
		~sprite();
		void draw() override;
		int createAnimation(const char* firstFrameFilePathImage);
		void playAnimation(int animationID);
		void stopAnimation(int animationID);
		void setAnimationSpeed(int animationID, float speed);
		void addFrameToAnimation(int animationID, const char* filePathImage);

	private:
		void setShader(unsigned int texture);
		unsigned int getCurrentTextureToDraw();
		unsigned int baseTextureID;
		std::vector<animation*> animations;
	};
}