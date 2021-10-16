#pragma once
#include "exports.h"
#include "entity2D.h"
#include <vector>
#include "atlasConfig.h"

namespace engine
{
	struct textureData;
	class animation;

	class ENGINE_API sprite : public entity2D
	{
	public:
		sprite(renderer* render, const char* filePathImage, bool invertImage);
		~sprite();
		void draw() override;
		textureData* createAnimationAtlas(const char* AtlasFilepath, bool invertImage);
		void deleteAnimationAtlas(textureData* atlas);
		int createAnimation(textureData* animationAtlasData, int columns, int rows);
		int createAnimation(textureData* animationAtlasData, atlasCutConfig config);
		void playAnimation(int animationID);
		void stopAnimation(int animationID);
		void stopAllAnimations();
		void setAnimationSpeed(int animationID, float speed);
	private:
		void setShader(unsigned int texture);
		unsigned int getCurrentTextureIDToDraw();
		void BindAnimationTexture(int i);
		void BindBaseTexture();
		textureData* baseTexture;
		int lastAnimationIndex = 0;
		std::vector<animation*> animations;
	};
}