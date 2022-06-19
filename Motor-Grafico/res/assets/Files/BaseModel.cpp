//========================================================================
// Copyright (c) Yann Clotioloman Yeo, 2017 
//
//	Author					: Yann Clotioloman Yeo
//	E-Mail					: trylzengine@outlook.com
//========================================================================

#include "stdafx.h"

#include "BaseModel.h"
#include "ModelLoadException.h"
#include <3rdPArty/Assimp/include/Importer.hpp>
#include <3rdPArty/Assimp/include/postprocess.h>

namespace Graphics { namespace Model
{
BaseModel::BaseModel(const std::string& path)
{
	this->loadModel(path);
}

BaseModel::~BaseModel()
{
	for (auto image : m_imageContainer)
	{
		delete image.second;
	}

	for (auto material : m_materialContainer)
	{
		delete material.second;
	}

	for (auto mesh : m_meshContainer)
	{
		delete mesh;
	}
}

void BaseModel::loadModel(const std::string& path)
{
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices);

	// Check for errors
	bool success = scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode;
	if (!success)
	{
		throw ModelLoadException("Enable to load model path = " + path);
	}

	// Retrieve the directory path of the filepath
	this->m_directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->processNode(scene->mRootNode, scene);
}

void BaseModel::processNode(aiNode* node, const aiScene* scene)
{
	// Process each mesh located at the current node
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->addMesh(mesh, scene);
	}

	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

void BaseModel::addMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	// Walk through each of the mesh's vertices
	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// Position
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		// Normal
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		vertex.normal = glm::normalize(vertex.normal);

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;

			vertex.texCoord = vec;
		}
		else
		{
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (uint32_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Process material.
	Material* material = new Material();
	const auto materialIndex = mesh->mMaterialIndex;

	if (materialIndex >= 0u)
	{
		auto materialIter = m_materialContainer.find(materialIndex);
		if (materialIter != m_materialContainer.end())
		{
			material = materialIter->second;
		}
		else
		{
			aiMaterial* aiMaterial = scene->mMaterials[materialIndex];

			aiColor3D color(0.f, 0.f, 0.f);
			if (aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
				material->m_diffuse = glm::vec3(color.r, color.g, color.b);

			if (aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
				material->m_specular = glm::vec3(color.r, color.g, color.b);

			if (aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
				material->m_ambient = glm::vec3(color.r, color.g, color.b);

			if (aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
				material->m_emissive = glm::vec3(color.r, color.g, color.b);

			if (aiMaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, color) == AI_SUCCESS)
				material->m_transparent = glm::vec3(color.r, color.g, color.b);

			float aiValue = 0.0f;
			if (aiMaterial->Get(AI_MATKEY_OPACITY, aiValue) == AI_SUCCESS)
				material->m_opacity = aiValue;

			if (aiMaterial->Get(AI_MATKEY_SHININESS, aiValue) == AI_SUCCESS)
				material->m_shininess = std::min(aiValue, Material::maxShininess);

			if (aiMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, aiValue) == AI_SUCCESS)
				material->m_specularStrength = aiValue;
			
			if (aiMaterial->Get(AI_MATKEY_REFRACTI, aiValue) == AI_SUCCESS)
			{
					if (Math::isApprox(aiValue, 1.0f, 1e-4f))
					{
						// Only air can have a refractive index thats is exactly one.
						aiValue = 1.002f;
					}

					material->m_refractiveIndex = aiValue;
					material->m_InvRefractiveIndex = 1.0f / aiValue;
			}

			if (material->m_refractiveIndex >= refractIdxTresholdHackForMirrors)
				material->m_type = Material::Type::PerfectMirror;
			else if (material->m_refractiveIndex >= refractIdxTresholdHackForMetals)
				material->m_type = Material::Type::Metal;
			else
				material->m_type = Material::Type::Dieletric;

			if (material->m_type == Material::Type::Dieletric)
			{
				material->m_fresnel0 = std::powf((material->m_refractiveIndex - 1.0f) / (material->m_refractiveIndex + 1.0f), 2.0f);
			}
			else
			{
				// Use specular channel average.
				material->m_fresnel0 = (material->m_specular.r + material->m_specular.g + material->m_specular.b) / 3.0f;
			}

			material->m_precomputedHemisphericalShininess = material->m_shininess / Material::maxShininess;

			material->m_diffuseImageId = this->loadMaterialImage(aiMaterial, aiTextureType_DIFFUSE);
			material->m_specularImageId = this->loadMaterialImage(aiMaterial, aiTextureType_SPECULAR);

			m_materialContainer.emplace(materialIndex, material);
		}
	}

	this->m_meshContainer.push_back(new Mesh(vertices, indices, materialIndex));
}


ImageIdentifier BaseModel::loadMaterialImage(aiMaterial* mat, aiTextureType aiType)
{
	auto textureCount = mat->GetTextureCount(aiType);
	if (textureCount == 0u)
	{
		return "";
	}

	if (textureCount > 1u)
	{
		aiString matName;
		if (mat->Get(AI_MATKEY_NAME, matName) == AI_SUCCESS)
		{
			TRACE("Material name = " << matName.C_Str() << "has more than one texture for aiTextureType = " << static_cast<int>(aiType));
		}
	}

	aiString aiStr;
	mat->GetTexture(aiType, 0, &aiStr);

	ImageIdentifier imageId(aiStr.C_Str());

	// Check if image was loaded before and if so skip loading a new image.
	auto iter = m_imageContainer.find(imageId);
	if (iter != m_imageContainer.end())
	{
		return imageId;
	}

	auto image = new Texture::RGBAImage();
	if (image->initFromFile(imageId))
	{
		this->m_imageContainer.emplace(imageId, image);

		return imageId;
	}

	delete image;

	return "";
}

const Material* BaseModel::getMaterial(const MaterialIdentifier& id) const
{
	return getMutableMaterial(id);
}

Material* BaseModel::getMutableMaterial(const MaterialIdentifier& id) const
{
	auto iter = m_materialContainer.find(id);
	assert(iter != m_materialContainer.end());

	return iter->second;
}

const Texture::RGBAImage* BaseModel::getImage(const ImageIdentifier& id) const
{
	auto iter = m_imageContainer.find(id);
	assert(iter != m_imageContainer.end());

	return iter->second;
}

const std::vector<Mesh*>& BaseModel::getMeshes() const
{
	return m_meshContainer;
}

const std::string& BaseModel::getDirectory() const
{
	return m_directory;
}

const ImageContainer& BaseModel::getImageContainer() const
{
	return m_imageContainer;
}
}}