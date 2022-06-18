#include "node.h"
#include <list>

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
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO);
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setLocalModel(localModel * children[i]->getModel());
			children[i]->draw();
		}
	}

	void node::setRenderer(renderer* renderer)
	{
		_renderer = renderer;

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setRenderer(renderer);
		}
	}

	void node::setMeshes(vector<Mesh> meshes)
	{
		this->meshes = meshes;
	}

	void node::setName(string name)
	{
		this->name = name;
	}

	void node::setChildren(vector<node*> children)
	{
		this->children = children;
	}

	void node::setParent(node* parent)
	{
		this->parent = parent;
	}

	void node::deinit()
	{
	}
}