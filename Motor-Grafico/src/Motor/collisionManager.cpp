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
	void collisionManager::AddToCollisionList(entity2D* entityToAdd, bool isStatic)
	{
		entityToAdd->setCollisionManager(this);
		isStatic ? staticCollisionList.push_back(entityToAdd) : dynamicCollisionList.push_back(entityToAdd);
	}
	void collisionManager::RemoveFromCollisionList(entity2D* entityToRemove)
	{
		staticCollisionList.remove(entityToRemove);
		dynamicCollisionList.remove(entityToRemove);
	}
}