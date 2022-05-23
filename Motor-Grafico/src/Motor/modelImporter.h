#pragma once
#include "Model.h"
#include "renderer.h"
#include "myMesh.h"
#include <list>

namespace engine
{

	class ENGINE_API modelImporter
	{
	public:
		modelImporter();
		~modelImporter();
		static vector<myMesh> loadModel(std::string path);
	private:
		static myVertex convertType(Vertex vertex);
		static myTexture convertType(Texture texture);
	};
}