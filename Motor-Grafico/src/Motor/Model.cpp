#include "Model.h"
#include "textureImporter.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace engine
{
	void Model::loadModel(string path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		sceneNode = new node();
		processNode(scene->mRootNode, scene, sceneNode, glm::mat4(1.f));
		sceneNode->setParent(NULL);
	}
	void Model::processNode(aiNode* node, const aiScene* scene, engine::node* parent, glm::mat4 mat)
	{
		engine::node* myNode = new engine::node();
		std::string name = node->mName.C_Str();		

		// process all the node's meshes (if any)
		if (name.find("$AssimpFbx$") == -1 && node->mNumMeshes == 0 && mat == glm::mat4(1.f))
		{
			if (name.find("RotationPivot") != -1 && name.find("Inverse") == -1)
			{
				aiMatrix4x4 matrix = node->mTransformation;
			
				mat[0][0] = (float)matrix.a1; mat[0][1] = (float)matrix.b1;  mat[0][2] = (float)matrix.c1; mat[0][3] = (float)matrix.d1;
				mat[1][0] = (float)matrix.a2; mat[1][1] = (float)matrix.b2;  mat[1][2] = (float)matrix.c2; mat[1][3] = (float)matrix.d2;
				mat[2][0] = (float)matrix.a3; mat[2][1] = (float)matrix.b3;  mat[2][2] = (float)matrix.c3; mat[2][3] = (float)matrix.d3;
				mat[3][0] = (float)matrix.a4; mat[3][1] = (float)matrix.b4;  mat[3][2] = (float)matrix.c4; mat[3][3] = (float)matrix.d4;
			}
			if (name.find("Pivot") == -1)
			{
				glm::mat4 m;
				aiMatrix4x4 matrix = node->mTransformation;
			
				m[0][0] = (float)matrix.a1; m[0][1] = (float)matrix.b1;  m[0][2] = (float)matrix.c1; m[0][3] = (float)matrix.d1;
				m[1][0] = (float)matrix.a2; m[1][1] = (float)matrix.b2;  m[1][2] = (float)matrix.c2; m[1][3] = (float)matrix.d2;
				m[2][0] = (float)matrix.a3; m[2][1] = (float)matrix.b3;  m[2][2] = (float)matrix.c3; m[2][3] = (float)matrix.d3;
				m[3][0] = (float)matrix.a4; m[3][1] = (float)matrix.b4;  m[3][2] = (float)matrix.c4; m[3][3] = (float)matrix.d4;
			
				mat *= m;
			}

			myNode->setMatrix(mat);
		}
		else
		{
			if (node->mNumMeshes > 0)
			{
				vector<Mesh> nodeMeshes;
				for (unsigned int i = 0; i < node->mNumMeshes; i++)
				{
					aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
					nodeMeshes.push_back(processMesh(mesh, scene));
				}

				myNode->setMeshes(nodeMeshes);
			}
		}

		if (name.find("bspPlane") != -1 || name.find("plane") != -1)
		{
			//myNode->setMatrix(mat);

			if (name.find("bspPlane") != -1)
			{
				bspPlanes.push_back(myNode);
			}
		}

		// then do the same for each of its children
		vector<engine::node*> childrenNodes;

		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, myNode, mat);
		}

		//if (name.find("$AssimpFbx$") == -1)
		//{
			//myNode->setMatrix(mat);
			parent->addChild(myNode);
			myNode->setName(name);
			myNode->setParent(parent);
		//}

		//for (unsigned int i = 0; i < node->mNumChildren; i++)
		//{
		//	engine::node* myNodeChild = new engine::node();
		//	processNode(node->mChildren[i], scene, myNodeChild);
		//
		//	myNodeChild->setParent(myNode);
		//	myNodeChild->UseLocalMatrix();
		//	childrenNodes.push_back(myNodeChild);
		//}

		//if (childrenNodes.size() > 0)
		//	myNode->setChildren(childrenNodes);
	}
	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			Vertex vertex;

			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			
			vertices.push_back(vertex);
		}

		// process indices
		

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}
	vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				Texture texture;
				texture.id = textureImporter::TextureFromFile(str.C_Str(), directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture); // add to loaded textures
			}
		}
		return textures;
	}
}
