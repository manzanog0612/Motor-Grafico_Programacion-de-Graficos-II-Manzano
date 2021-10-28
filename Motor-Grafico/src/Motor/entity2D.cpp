#include "entity2D.h"
#include "collisionManager.h"

namespace engine
{
	entity2D::entity2D()
	{
		colManager = nullptr;
	}
	entity2D::~entity2D()
	{

	}
	void entity2D::setCollisionManager(collisionManager* colManager)
	{
		this->colManager = colManager;
	}
}