#pragma once
#include "exports.h"
#include "entity2D.h"

namespace engine
{
	class ENGINE_API shape abstract : public entity2D
	{
	public:
		shape();
		~shape();

	private:
	};
}