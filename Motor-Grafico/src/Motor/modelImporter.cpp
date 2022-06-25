#include "modelImporter.h"

namespace engine
{
	modelImporter::modelImporter()
	{
	}

	modelImporter::~modelImporter()
	{
	}

	node* modelImporter::chargeBaseNodeInfo(std::string path)
	{
		Model* newModel = new engine::Model(path);

		if (path[path.size() - 3] == 'f' && path[path.size() - 2] == 'b' && path[path.size() - 1] == 'x')
		{
			newModel->GetBaseNode()->dontDraw();
		}

		return newModel->GetBaseNode();
	}
}