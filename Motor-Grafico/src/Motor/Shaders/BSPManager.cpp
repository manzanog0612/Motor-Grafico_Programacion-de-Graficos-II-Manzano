#include "../BSPManager.h"

namespace engine
{
	void BSPManager::setCameraEntityForCheck(entity* camera)
	{
		this->camera = camera;
	}

	void BSPManager::addEnityToTackList(node* entity)
	{
		entities.push_back(entity);
	}

	void BSPManager::flagAllTrackEntities()
	{
		for (int i = 0; i < entities.size(); i++)
		{

		}
	}
}