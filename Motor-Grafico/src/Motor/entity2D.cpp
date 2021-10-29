#include "entity2D.h"
#include "collisionManager.h"
#include <math.h>      
#include <algorithm>

using namespace std;

namespace engine
{
	entity2D::entity2D()
	{
		colManager = nullptr;
		col.width = 0;
		col.height = 0;
	}
	entity2D::~entity2D()
	{

	}
	void entity2D::setCollider(float height, float width)
	{
		col.width = width;
		col.height = height;
	}
	collider entity2D::getCollider()
	{
		return col;
	}
	void entity2D::setCollisionManager(collisionManager* colManager)
	{
		this->colManager = colManager;
	}
	bool entity2D::checkCollision(entity2D& target, float &xOverlap, float &yOverlap)
	{
		collider tarCol = target.getCollider();

		xOverlap = max(0.0f,
			min(getPos().x + fabs(getScale().x) / 2.0f, target.getPos().x + fabs(target.getScale().x) / 2.0f) -
			max(getPos().x - fabs(getScale().x) / 2.0f, target.getPos().x - fabs(target.getScale().x) / 2.0f));

		yOverlap = max(0.0f,
			min(getPos().y + fabs(getScale().y) / 2.0f, target.getPos().y + fabs(target.getScale().y) / 2.0f) -
			max(getPos().y - fabs(getScale().y) / 2.0f, target.getPos().y - fabs(target.getScale().y) / 2.0f));

		return xOverlap != 0.0f && yOverlap != 0.0f;
		//{
		//	if (xOverlap > yOverlap)
		//	{
		//		if (getPos().y < 0 && getPos().y < target.getPos().y || getPos().y > 0 && getPos().y < target.getPos().y)
		//		{
		//
		//		}
		//		else if (getPos().y < 0 && getPos().y > target.getPos().y || getPos().y > 0 && getPos().y > target.getPos().y)
		//		{
		//
		//		}
		//	}
		//	else
		//	{
		//
		//	}
		//}

		
	}
}