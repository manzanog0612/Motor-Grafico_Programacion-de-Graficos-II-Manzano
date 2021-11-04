#pragma once
#include <list>

namespace engine
{

	class entity2D;

	class collisionManager
	{
	public:
		collisionManager();
		~collisionManager();
		void AddToCollisionList(entity2D* entityToAdd, bool isStatic);
		void RemoveFromCollisionList(entity2D* entityToRemove);

	private:
		std::list<entity2D*> dynamicCollisionList;
		std::list<entity2D*> staticCollisionList;
	};
}