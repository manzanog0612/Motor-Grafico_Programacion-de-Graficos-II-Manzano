#include "node.h"

namespace engine
{
	node::node()
	{

	}

	node::node(renderer* render, std::string path)
	{
		_renderer = render;

		//meshes = modelImporter::chargeEntity3D(path);
	}

	node::~node()
	{
	}

	vector<node>* node::getChildren()
	{
		return children;
	}

	int node::getChildrenAmount()
	{
		return children->size();
	}

	void node::draw()
	{
		_renderer->setMVP(model);

		for (int i = 0; i < meshes.size(); i++)
		{
				_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO);
		}
	}

	void node::deinit()
	{
	}
}