#pragma once
#include "myMesh.h"

using namespace std;

namespace engine
{
	class ENGINE_API myModel
	{
	public:
		vector<myTexture> textures_loaded;
		vector<myMesh> meshes;
		string directory;
	private:

	};
}