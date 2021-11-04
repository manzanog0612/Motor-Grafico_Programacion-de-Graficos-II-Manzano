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

		for (auto const& d1 : dynamicCollisionList) {
			for (auto const& d2 : dynamicCollisionList) {
				if(d1 != d2)
				{
					float overlapX = 0;
					float overlapY = 0;
					collisionType currentCollision = d1->checkCollision(*d2, overlapX, overlapY);
					if (currentCollision != collisionType::none)
					{
						d1->applyCollisionRestrictions(currentCollision, overlapX, overlapY, true);
					}
					overlapX = 0;
					overlapY = 0;
					currentCollision = d2->checkCollision(*d1, overlapX, overlapY);
					if (currentCollision != collisionType::none)
					{
						d2->applyCollisionRestrictions(currentCollision, overlapX, overlapY, true);
					}
				}
			}
		}

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