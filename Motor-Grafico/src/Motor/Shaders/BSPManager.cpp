#include "../BSPManager.h"

namespace engine
{
	void BSPManager::setCameraEntityForCheck(engine::camera* camera)
	{
		this->_camera = camera;
	}

	void BSPManager::addEnityToTrackList(node* entity)
	{
		entities.push_back(entity);
	}

	void BSPManager::addPlaneToTrackList(plane* plane)
	{
		planes.push_back(plane);
	}

	void BSPManager::flagAllTrackEntities()
	{
		for (int i = 0; i < planes.size(); i++)
		{
			for (int j = 0; j < entities.size(); j++)
			{
				entities[j]->setDrawThisFrame(planes[i]->SameSide(entities[j]->getPos(), this->_camera->getPos()));
			}
		}
	}
}