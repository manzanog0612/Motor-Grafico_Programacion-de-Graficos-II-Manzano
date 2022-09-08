#include "BSPManager.h"

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
			if (!planes[i]->GetSide(_camera->getPos()))
			{
				planes[i]->Flip();
			}
		}

		for (int i = 0; i < entities.size(); i++)
		{
			entities[i]->checkBSP(planes, this->_camera->getPos());
		}
	}
}