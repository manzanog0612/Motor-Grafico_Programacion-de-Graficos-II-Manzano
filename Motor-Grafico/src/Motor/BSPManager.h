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
		void setCameraEntityForCheck(camera* camera);
		void addEnityToTrackList(node* entity);
		void addPlaneToTrackList(plane* plane);
		void flagAllTrackEntities();
	private:
		vector<node*> entities;
		vector<plane*> planes;
		camera* _camera;
	};
}

#endif
