#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{

	class collisionManager;

	struct collider
	{
		float height;
		float width;
	};

	class ENGINE_API entity2D : public entity
	{
	public:
		entity2D();
		~entity2D();
		void setCollider(float height, float width);
		collider getCollider();
		void setCollisionManager(collisionManager* colManager);
		bool checkCollision(entity2D& target, float& xOverlap, float& yOverlap);
	private:
		collisionManager* colManager;
		collider col;
	};
}