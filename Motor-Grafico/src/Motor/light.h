#pragma once
#include "exports.h"
#include "renderer.h"

namespace engine
{
	class ENGINE_API light
	{
	public:
		light();
		light(renderer* render);
		~light();
		void draw();
	private:
		unsigned int VAO, VBO;
		renderer* _renderer;
	};
}