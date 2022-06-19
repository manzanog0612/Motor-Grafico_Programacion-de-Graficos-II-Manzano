#include "node.h"
//#include <list>
#include <random>
namespace engine
{
	node::node()
	{
		
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

	void node::draw()
	{
		if (parent == NULL)
		{
			_renderer->setMVP(model);
			setLocalModel(model);
		}
		else
		{
			_renderer->setMVP(localModel);
		}
		
		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO, color);
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setLocalModel(localModel * children[i]->getModel());
			children[i]->draw();
		}

		if (aabb.size() > 0)
		{
			aabbShapes[0]->setPos(glm::vec3(aabb[0].x, aabb[1].y, aabb[1].z));
			aabbShapes[1]->setPos(glm::vec3(aabb[1].x, aabb[1].y, aabb[1].z));
			aabbShapes[2]->setPos(glm::vec3(aabb[0].x, aabb[0].y, aabb[1].z));
			aabbShapes[3]->setPos(glm::vec3(aabb[1].x, aabb[0].y, aabb[1].z));
			aabbShapes[4]->setPos(glm::vec3(aabb[0].x, aabb[1].y, aabb[0].z));
			aabbShapes[5]->setPos(glm::vec3(aabb[1].x, aabb[1].y, aabb[0].z));
			aabbShapes[6]->setPos(glm::vec3(aabb[0].x, aabb[0].y, aabb[0].z));
			aabbShapes[7]->setPos(glm::vec3(aabb[1].x, aabb[0].y, aabb[0].z));

			for (int i = 0; i < AMOUNT_BOUNDS; i++)
			{
				aabbShapes[i]->setLocalModel(localModel * aabbShapes[i]->getModel());
				aabbShapes[i]->draw(aabbShapes[i]->getLocalModel());
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