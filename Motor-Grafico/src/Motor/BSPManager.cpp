#include "BSPManager.h"

namespace engine
{
	BSPManager::~BSPManager()
	{
		for (int i = 0; i < planes.size(); i++)
		{
			delete planes[i];
		}
	}
	void BSPManager::setCameraEntityForCheck(engine::camera* camera)
	{
		this->_camera = camera;
	}

	void BSPManager::addEnityToTrackList(node* entity)
	{
		entities.push_back(entity);
	}

	void BSPManager::addPlanesToTrackList(vector<node*> bspPlanes)
	{
		planesEntities = bspPlanes;

		for (int i = 0; i < bspPlanes.size(); i++)
		{
			glm::vec3 forward = normalize(bspPlanes[i]->getUpConst());
			plane* bspPlane = new engine::plane(forward, bspPlanes[i]->getPos());
			planes.push_back(bspPlane);
		}
	}

	void BSPManager::setRendererForPlanes(renderer* render)
	{
		for (int i = 0; i < planesEntities.size(); i++)
		{
			planesEntities[i]->setRenderer(render);
		}
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
	void BSPManager::drawPlanes()
	{
		for (int i = 0; i < planesEntities.size(); i++)
		{
			planesEntities[i]->drawForced();
		}
	}
}