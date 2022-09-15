#include "modelImporter.h"

namespace engine
{
	modelImporter::modelImporter()
	{
	}

	modelImporter::~modelImporter()
	{
	}

	Model* modelImporter::chargeBaseNodeInfo(std::string path)
	{
		Model* newModel = new engine::Model(path);

		return newModel;
	}
}