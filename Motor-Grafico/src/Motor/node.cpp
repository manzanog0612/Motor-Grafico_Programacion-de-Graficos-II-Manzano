#include "node.h"
#include "occlusionCulling.h"
//#include <list>


#include <random>
namespace engine
{
	node::node()
	{
		drawThisFrame = false;
		drawFirstParent = true;
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
		drawThisFrame = false;

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setWorldModelWithParentModel(worldModel);
			children[i]->setTransformations(lastChilds);
			addBoundsToAABB(children[i]->getLocalAABB());
			updateAABBPositions();

			if (children[i]->canDrawThisFrame())
			{
				allowDrawThisFrame();
			}
		}

		if (getChildrenAmount() == 0)
		{
			updateAABBPositions();
		}

		if (!drawThisFrame && OcclusionCulling::IsOnView(aabbPositions))
		{
			allowDrawThisFrame();
		}

		if (!drawThisFrame)
		{
			if (name == "pCylinder4" || name == "pCylinder2" || name == "pCylinder1" || name == "group1" || name == "pCube2")
			{
				cout << name << " node not drawn" << endl;
			}
		}
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
		if (drawThisFrame)
		{	
			_renderer->setMVP(worldModel);
		
			for (int i = 0; i < meshes.size(); i++)
			{
				_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO, color);
			}

			if (localAABB.size() > 0)
			{
				for (int i = 0; i < AMOUNT_BOUNDS; i++)
				{
					aabbShapes[i]->draw(aabbShapes[i]->getModel());
				}
			}
		}
	}

	void node::drawAsParent()
	{
		lastChilds->clear();

		setTransformations(lastChilds);
	}

	void node::drawAsChild()
	{
		draw();

		if (parent != NULL)
		{
			parent->drawAsChild();
		}
	}

	void node::checkIfDrawAsChild()
	{
		if (OcclusionCulling::IsOnView(localAABB))
		{
			drawAsChild();
		}
		else
		{
			
			if (parent != NULL)
			{
				parent->checkIfDrawAsChild();
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
		UseLocalMatrix();

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setRenderer(renderer);
			children[i]->setColor(glm::vec4(1, 1, 1, 1));
		}

		glm::vec4 color = glm::vec4(getRandomNumber(0, 1), getRandomNumber(0, 1), getRandomNumber(0, 1), 1);
		for (int i = 0; i < AMOUNT_BOUNDS; i++)
		{
			aabbShapes[i] = new engine::shape(renderer, engine::SHAPE::CUBE, engine::MATERIAL::PEARL);
			aabbShapes[i]->UseLocalMatrix();
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

	bool node::canDrawThisFrame()
	{
		return drawThisFrame;
	}

	void node::drawDebug()
	{
		_renderer->setMVP(worldModel);


		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO, color);
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setWorldModelWithParentModel(worldModel);
			children[i]->drawDebug();
			//addBoundsToAABB(children[i]->getLocalAABB());
		}

	}

	void node::allowDrawThisFrame()
	{
		drawThisFrame = true;
		draw();
	}

	void node::updateAABBPositions()
	{
		if (localAABB.size() > 0)
		{
			aabbPositions.clear();

			aabbShapes[0]->setPos(glm::vec3(localAABB[0].x, localAABB[1].y, localAABB[1].z));
			aabbShapes[1]->setPos(glm::vec3(localAABB[1].x, localAABB[1].y, localAABB[1].z));
			aabbShapes[2]->setPos(glm::vec3(localAABB[0].x, localAABB[0].y, localAABB[1].z));
			aabbShapes[3]->setPos(glm::vec3(localAABB[1].x, localAABB[0].y, localAABB[1].z));
			aabbShapes[4]->setPos(glm::vec3(localAABB[0].x, localAABB[1].y, localAABB[0].z));
			aabbShapes[5]->setPos(glm::vec3(localAABB[1].x, localAABB[1].y, localAABB[0].z));
			aabbShapes[6]->setPos(glm::vec3(localAABB[0].x, localAABB[0].y, localAABB[0].z));
			aabbShapes[7]->setPos(glm::vec3(localAABB[1].x, localAABB[0].y, localAABB[0].z));

			for (int i = 0; i < AMOUNT_BOUNDS; i++)
			{
				aabbShapes[i]->setWorldModelWithParentModel(worldModel);

				aabbPositions.push_back(aabbShapes[i]->getPosFromTransformMatrix());
			}
		}
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