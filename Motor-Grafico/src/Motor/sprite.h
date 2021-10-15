#pragma once
#include "exports.h"
#include "entity2D.h"
#include <vector>

namespace engine
{

	struct textureData;
	class animation;

	class ENGINE_API sprite : public entity2D
	{
	public:
		sprite(renderer* render, const char* filePathImage);
		~sprite();
		void draw() override;
		int createAnimation(const char* AtlasFilepath, int columns, int rows);
		void playAnimation(int animationID);
		void stopAnimation(int animationID);
		void setAnimationSpeed(int animationID, float speed);
	private:
		void setShader(unsigned int texture);
		unsigned int getCurrentTextureIDToDraw();
		void BindAnimationTexture(int i);
		void BindBaseTexture();
		textureData* baseTexture;
		std::vector<animation*> animations;
	};
}