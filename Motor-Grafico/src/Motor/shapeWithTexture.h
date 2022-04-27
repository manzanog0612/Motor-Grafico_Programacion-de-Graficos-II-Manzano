#pragma once
#include "exports.h"
#include "entity.h"
#include "renderer.h"
#include "atlasConfig.h"

namespace engine
{
	enum class SHAPE { TRIANGLE, QUAD, CUBE };

	class ENGINE_API shapeWithTexture : public entity
	{
	public:
		shapeWithTexture(renderer* render, SHAPE shape, const char* filePathImage, bool invertImage, bool affectedByLight, MATERIAL material);
		~shapeWithTexture();
		void draw() override;
		void modifyBaseTextureCoords(atlasCutConfig config);
		void setTextureCoordinates(glm::vec2 coord1, glm::vec2 coord2, glm::vec2 coord3, glm::vec2 coord4);
		void setTexture(renderer* render, const char* filePathImage, bool invertImage);
		void deinit();
	private:
		//void setShader();
		bool affectedByLight;
		unsigned int bufferPosUVs = 0;
		glm::vec2 baseUVCoords[4];
		void bindBaseUVCoords();
		textureData* baseTexture;
		MATERIAL material;
	};
}