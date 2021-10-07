#pragma once
#include "exports.h"
#include "entity2D.h"

namespace engine
{
	class ENGINE_API sprite : public entity2D
	{
	public:
		sprite(renderer* render, const char* filePathImage);
		~sprite();
		void draw() override;
	private:
		void setShader() override;
		int textureWidth;
		int textureHeight;
		int numberOfColorChannels;
		unsigned int textureID;
	};
}