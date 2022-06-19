//========================================================================
// Copyright (c) Yann Clotioloman Yeo, 2017 
//
//	Author					: Yann Clotioloman Yeo
//	E-Mail					: trylzengine@outlook.com
//========================================================================

#pragma once

#include "Material.h"
#include "Mesh.h"

#include <memory>
#include <3rdPArty/Assimp/include/scene.h>

namespace Graphics { namespace Model
{
// Since we don't have an editor so we use the refractive index to set a material type.

// Materials with a refractive index in [refractIdxTresholdHackForMetals; refractIdxTresholdHackForMetals[ are METALS.
constexpr float refractIdxTresholdHackForMetals = 6.0f;

// Materials over or equals to refractIdxTresholdHackForMetals are MIRRORS.
constexpr float refractIdxTresholdHackForMirrors = 8.0f;

class BaseModel
{
public:
	BaseModel(const std::string& path);

	virtual ~BaseModel();

	const Material* getMaterial(const MaterialIdentifier& id) const;
	Material* getMutableMaterial(const MaterialIdentifier& id) const;

	const Texture::RGBAImage* getImage(const ImageIdentifier& id) const;
	const std::vector<Mesh*>& getMeshes() const;

	const std::string& getDirectory() const;
	const ImageContainer& getImageContainer() const;


protected:
	std::vector<Mesh*> m_meshContainer;

	ImageContainer m_imageContainer;
	std::map<MaterialIdentifier, Material*> m_materialContainer;

private:
	std::string m_directory;

	// Assimp loading functions
	// @See: https://learnopengl.com/#!Model-Loading/Mesh
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	void addMesh(aiMesh* mesh, const aiScene* scene);
	ImageIdentifier loadMaterialImage(aiMaterial* mat, aiTextureType aiType);
};
}}