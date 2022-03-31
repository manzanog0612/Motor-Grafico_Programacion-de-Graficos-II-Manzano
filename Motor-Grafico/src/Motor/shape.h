#pragma once
#include "exports.h"
#include "entity2D.h"

namespace engine
{
	class ENGINE_API shape : public entity2D
	{
	public:
		shape(renderer* render, unsigned int vert, bool affectedByLight);
		~shape();
		void draw() override;
	private:
		//void setShader();
	};
}