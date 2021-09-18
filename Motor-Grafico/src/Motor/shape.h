#pragma once
#include "exports.h"
#include "entity2D.h"

namespace engine
{
	class ENGINE_API shape : public entity2D
	{
	public:
		shape(unsigned int vertices);
		~shape();
		void draw();

	protected:
		unsigned int VAO, VBO, EBO, _vertices;
	};
}