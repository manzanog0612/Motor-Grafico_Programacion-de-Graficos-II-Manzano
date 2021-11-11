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
		void addToCollisionList(entity2D* entityToAdd, bool isStatic);
		void removeFromCollisionList(entity2D* entityToRemove);
		bool isInCollisionList(entity2D* entityToCheck);
		void updateCollisions();

	private:
		std::list<entity2D*> dynamicCollisionList;
		std::list<entity2D*> staticCollisionList;
	};
}