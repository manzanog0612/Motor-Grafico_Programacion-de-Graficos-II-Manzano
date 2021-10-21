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
		void modifyBaseTextureCoords(atlasCutConfig config);
		textureData* createAnimationAtlas(const char* AtlasFilepath, bool invertImage);
		void deleteAnimationAtlas(textureData* atlas);
		int createAnimation(atlasCutConfig config);
		int createAnimation(textureData* animationAtlasData, int columns, int rows);
		int createAnimation(textureData* animationAtlasData, atlasCutConfig config);
		void playAnimation(int animationID);
		void stopAnimation(int animationID);
		void stopAllAnimations();
		void setAnimationSpeed(int animationID, float speed);
		void setAnimationTimeBetweenFrames(int animationID, float time);
		void setAnimationFullTime(int animationID, float time);
	private:
		void setShader(unsigned int texture);
		unsigned int getCurrentTextureIDToDraw();
		unsigned int bufferPosUVs = 0;
		int lastCoordIndex = 0;
		glm::vec2 baseUVCoords[4];
		void bindCustomUVCoords(int i);
		void bindBaseUVCoords();
		textureData* baseTexture;
		std::vector<animation*> animations;
	};
}