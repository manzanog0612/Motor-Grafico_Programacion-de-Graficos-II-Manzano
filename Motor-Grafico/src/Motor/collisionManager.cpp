#include "collisionManager.h"
#include "entity2D.h"

namespace engine
{
	collisionManager::collisionManager()
	{

	}
	collisionManager::~collisionManager()
	{

	}
	void collisionManager::addToCollisionList(entity2D* entityToAdd, bool isStatic)
	{
		entityToAdd->setCollisionManager(this);
		isStatic ? staticCollisionList.push_back(entityToAdd) : dynamicCollisionList.push_back(entityToAdd);
	}
	void collisionManager::removeFromCollisionList(entity2D* entityToRemove)
	{
		staticCollisionList.remove(entityToRemove);
		dynamicCollisionList.remove(entityToRemove);
	}
	void collisionManager::updateCollisions()
	{
		for (auto const& d : dynamicCollisionList) {
			for (auto const& s : staticCollisionList) {
				float overlapX = 0;
				float overlapY = 0;
				collisionType currentCollision = d->checkCollision(*s, overlapX, overlapY);
				if(currentCollision != collisionType::none)
				{
					d->applyCollisionRestrictions(currentCollision, overlapX, overlapY, false);
				}
			}
		}
	}
}