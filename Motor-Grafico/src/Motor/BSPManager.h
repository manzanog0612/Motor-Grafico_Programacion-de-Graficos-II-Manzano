#ifndef BSPMANAGER_H
#define BSPMANAGER_H

#include "exports.h"
#include "node.h"
#include "plane.h"

namespace engine
{
	class ENGINE_API BSPManager
	{
	public:
		~BSPManager();
		void setCameraEntityForCheck(camera* camera);
		void addEnityToTrackList(node* entity);
		void addPlanesToTrackList(vector<node*> bspPlanes);
		void setRendererForPlanes(renderer* render);
		void flagAllTrackEntities();
		void drawPlanes();
	private:
		vector<node*> entities;
		vector<plane*> planes;
		vector<node*> planesEntities;
		camera* _camera;
	};
}

#endif
