#include "node.h"
//#include <list>


#include <random>
namespace engine
{
	node::node()
	{
		drawnThisFrame = false;
		lastChilds = new vector<node*>();
	}

	node::~node()
	{
	}

	vector<node*> node::getChildren()
	{
		return children;
	}

	int node::getChildrenAmount()
	{
		return children.size();
	}

	void node::setTransformations(vector<node*> *lastChilds)
	{
		if (parent == NULL)
		{
			_renderer->setMVP(localModel);
			//setWorldModelWithParentModel(localModel);
		}
		else
		{
			//_renderer->setMVP(localModel);
			_renderer->setMVP(localModel);
		}

		//if (getChildrenAmount() == 0)
		//{
		//	lastChilds->push_back(this);
		//}

		//drawnThisFrame = false;

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setWorldModelWithParentModel(localModel);
			children[i]->setTransformations(lastChilds);
			//addBoundsToAABB(children[i]->getLocalAABB());
		}

		//if (localAABB.size() > 0)
		//{
		//	aabbShapes[0]->setPos(glm::vec3(localAABB[0].x, localAABB[1].y, localAABB[1].z));
		//	aabbShapes[1]->setPos(glm::vec3(localAABB[1].x, localAABB[1].y, localAABB[1].z));
		//	aabbShapes[2]->setPos(glm::vec3(localAABB[0].x, localAABB[0].y, localAABB[1].z));
		//	aabbShapes[3]->setPos(glm::vec3(localAABB[1].x, localAABB[0].y, localAABB[1].z));
		//	aabbShapes[4]->setPos(glm::vec3(localAABB[0].x, localAABB[1].y, localAABB[0].z));
		//	aabbShapes[5]->setPos(glm::vec3(localAABB[1].x, localAABB[1].y, localAABB[0].z));
		//	aabbShapes[6]->setPos(glm::vec3(localAABB[0].x, localAABB[0].y, localAABB[0].z));
		//	aabbShapes[7]->setPos(glm::vec3(localAABB[1].x, localAABB[0].y, localAABB[0].z));
		//
		//	for (int i = 0; i < AMOUNT_BOUNDS; i++)
		//	{
		//		aabbShapes[i]->setLocalModel(localModel * aabbShapes[i]->getModel());
		//		aabbShapes[i]->draw(aabbShapes[i]->getLocalModel());
		//	}
		//}
	}

	void node::addBoundsToAABB(vector<glm::vec3> childAABB)
	{
		if (childAABB.size() < 1)
		{
			return;
		}
		else if (localAABB.size() < 1)
		{
			localAABB.clear();
			localAABB.push_back(childAABB[0]);
			localAABB.push_back(childAABB[1]);

			aabb.clear();
			aabb.push_back(childAABB[0]);
			aabb.push_back(childAABB[1]);

			return;
		}

		localAABB.clear();
		localAABB.push_back(aabb[0]);
		localAABB.push_back(aabb[1]);

		if (childAABB[0].x < localAABB[0].x) localAABB[0].x = childAABB[0].x;
		if (childAABB[1].x > localAABB[1].x) localAABB[1].x = childAABB[1].x;
		if (childAABB[0].y < localAABB[0].y) localAABB[0].y = childAABB[0].y;
		if (childAABB[1].y > localAABB[1].y) localAABB[1].y = childAABB[1].y;
		if (childAABB[0].z < localAABB[0].z) localAABB[0].z = childAABB[0].z;
		if (childAABB[1].z > localAABB[1].z) localAABB[1].z = childAABB[1].z;
	}

	void node::draw()
	{		
		//if (drawnThisFrame)
		//{
		//	return;
		//}

		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO, color);
		}

		//drawnThisFrame = true;

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->draw();
		}
	}

	void node::drawAsParent(Frustum frustum)
	{
		//lastChilds->clear();

		setTransformations(lastChilds);

		draw();
		for (int i = 0; i < lastChilds->size(); i++)
		{
			
			//lastChilds->at(i)
			//lastChilds->at(i)->checkIfDrawAsChild(frustum);
		}
	}

	void node::drawAsChild()
	{
		draw();

		if (parent != NULL)
		{
			parent->drawAsChild();
		}
	}

	void node::checkIfDrawAsChild(Frustum frustum)
	{
		if (isInsideCamera(frustum))
		{
			drawAsChild();
		}
		else
		{
			if (parent != NULL)
			{
				parent->checkIfDrawAsChild(frustum);
			}
		}
	}

	float node::getRandomNumber(float min, float max)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(mt);
	}

	void node::setRenderer(renderer* renderer)
	{
		_renderer = renderer;
		setColor(glm::vec4(1, 1, 1, 1));
		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setRenderer(renderer);
			children[i]->setColor(glm::vec4(1, 1, 1, 1));
		}

		glm::vec4 color = glm::vec4(getRandomNumber(0, 1), getRandomNumber(0, 1), getRandomNumber(0, 1), 1);
		for (int i = 0; i < AMOUNT_BOUNDS; i++)
		{
			aabbShapes[i] = new engine::shape(renderer, engine::SHAPE::CUBE, engine::MATERIAL::PEARL);
			aabbShapes[i]->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
			aabbShapes[i]->setColor(color);
		}
	}

	void node::setMeshes(vector<Mesh> meshes)
	{
		this->meshes = meshes;

		setAABB(this->meshes);
	}

	void node::setName(string name)
	{
		this->name = name;
	}

	void node::setChildren(vector<node*> children)
	{
		this->children = children;
	}

	string node::getName()
	{
		return name;
	}

	vector<glm::vec3> node::getLocalAABB()
	{
		return localAABB;
	}

	node* node::getChildWithName(string name)
	{
		if (this->name == name)
		{
			return this;
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			if (children[i]->getName() == name)
			{
				return children[i];
			}
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			node* node = children[i]->getChildWithName(name);

			if (node != NULL)
			{
				return node;
			}
		}

		return NULL;
	}

	bool node::isOnOrForwardPlan(Plan plan)
	{
		// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
		if (aabb.size() < 1)
		{
			return true;
		}

		glm::vec3 extents = glm::vec3(aabb[1].x - getPos().x, aabb[1].y - getPos().y, aabb[1].z - getPos().z);

		const float r = extents.x * std::abs(plan.normal.x) +
			extents.y * std::abs(plan.normal.y) + extents.z * std::abs(plan.normal.z);

		return -r <= plan.getSignedDistanceToPlan(getPos());
	}

	bool node::isInsideCamera(Frustum frustum)
	{
		return (meshes.size() > 0 && 
				isOnOrForwardPlan(frustum.leftFace) &&
				isOnOrForwardPlan(frustum.rightFace) &&
				isOnOrForwardPlan(frustum.topFace) &&
				isOnOrForwardPlan(frustum.bottomFace) &&
				isOnOrForwardPlan(frustum.nearFace) &&
				isOnOrForwardPlan(frustum.farFace));
	}

	void node::setParent(node* parent)
	{
		this->parent = parent;
	}

	void node::setAABB(vector<Mesh> meshes)
	{
		if (meshes.size() < 1)
		{
			return;
		}

		aabb.push_back(glm::vec3());
		aabb.push_back(glm::vec3());

		aabb[0].x = aabb[1].x = meshes[0].vertices[0].Position.x;
		aabb[0].y = aabb[1].y = meshes[0].vertices[0].Position.y;
		aabb[0].z = aabb[1].z = meshes[0].vertices[0].Position.z;

		for (int i = 0; i < meshes.size(); i++)
		{
			for (int j = 0; j < meshes[i].vertices.size(); j++) {
				if (meshes[i].vertices[j].Position.x < aabb[0].x) aabb[0].x = meshes[i].vertices[j].Position.x;
				if (meshes[i].vertices[j].Position.x > aabb[1].x) aabb[1].x = meshes[i].vertices[j].Position.x;
				if (meshes[i].vertices[j].Position.y < aabb[0].y) aabb[0].y = meshes[i].vertices[j].Position.y;
				if (meshes[i].vertices[j].Position.y > aabb[1].y) aabb[1].y = meshes[i].vertices[j].Position.y;
				if (meshes[i].vertices[j].Position.z < aabb[0].z) aabb[0].z = meshes[i].vertices[j].Position.z;
				if (meshes[i].vertices[j].Position.z > aabb[1].z) aabb[1].z = meshes[i].vertices[j].Position.z;
			}
		}

		localAABB.push_back(aabb[0]);
		localAABB.push_back(aabb[1]);
	}

	void node::deinit()
	{
		for (int i = 0; i < AMOUNT_BOUNDS; i++)
		{
			delete aabbShapes[i];
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->deinit();
			delete children[i];
		}
	}
}