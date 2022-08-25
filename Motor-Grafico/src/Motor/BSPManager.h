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
		void setCameraEntityForCheck(entity* camera);
		void addEnityToTackList(node* entity);
		void flagAllTrackEntities();
	private:
		vector<node*> entities;
		entity* camera;
	};
}

#endif
