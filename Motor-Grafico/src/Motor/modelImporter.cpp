#include "modelImporter.h"

namespace engine
{
	modelImporter::modelImporter()
	{
	}

	modelImporter::~modelImporter()
	{
	}

	vector<myMesh> modelImporter::loadModel(std::string path)
	{
		Model* newModel = new engine::Model(path);

		vector<myMesh> meshes;

		vector<Mesh> importerMeshes = newModel->GetMeshes();

		for (int i = 0; i < importerMeshes.size(); i++)
		{
			//Get all vertices
			vector<myVertex> myVertices;

			for (int j = 0; j < importerMeshes[i].vertices.size(); j++)
			{
				myVertices.push_back(convertType(importerMeshes[i].vertices[j]));
			}
			//Get all textures
			vector<myTexture> myTextures;

			for (int j = 0; j < importerMeshes[i].textures.size(); j++)
			{
				myTextures.push_back(convertType(importerMeshes[i].textures[j]));
			}
			
			meshes.push_back(myMesh(myVertices, importerMeshes[i].indices, myTextures, importerMeshes[i].VAO, importerMeshes[i].VBO, importerMeshes[i].EBO));
		}

		return meshes;
	}

	myVertex modelImporter::convertType(Vertex vertex)
	{
		myVertex myTypeVertex;

		myTypeVertex.Normal = vertex.Normal;
		myTypeVertex.Position = vertex.Position;
		myTypeVertex.TexCoords = vertex.TexCoords;

		return myTypeVertex;
	}
	myTexture modelImporter::convertType(Texture texture)
	{
		myTexture myTypeTexture;

		myTypeTexture.id = texture.id;
		myTypeTexture.path = texture.path;
		myTypeTexture.type = texture.type;

		return myTypeTexture;
	}
}