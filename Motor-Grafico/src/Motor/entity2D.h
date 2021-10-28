#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{

	class collisionManager;

	class ENGINE_API entity2D : public entity
	{
	public:
		entity2D();
		~entity2D();
		void setCollisionManager(collisionManager* colManager);
	private:
		collisionManager* colManager;
	};
}