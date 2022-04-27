#include "shapeWithTexture.h"
#include "textureImporter.h"
#include "renderer.h"
#include "vertexs.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	shapeWithTexture::~shapeWithTexture()
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = nullptr;

		baseUVCoords[0] = { 1.0f, 1.0f };
		baseUVCoords[1] = { 1.0f, 0.0f };
		baseUVCoords[2] = { 0.0f, 0.0f };
		baseUVCoords[3] = { 0.0f, 1.0f };
	}
	shapeWithTexture::shapeWithTexture(renderer* render, SHAPE shape, const char* filePathImage, bool invertImage, bool affectedByLight, MATERIAL material)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;
		this->affectedByLight = affectedByLight;
		this->material = material;

		baseUVCoords[0] = { 1.0f, 1.0f };
		baseUVCoords[1] = { 1.0f, 0.0f };
		baseUVCoords[2] = { 0.0f, 0.0f };
		baseUVCoords[3] = { 0.0f, 1.0f };

		setTexture(render, filePathImage, invertImage);
	}
	void shapeWithTexture::draw()
	{
		_renderer->shaderPro.use();
		unsigned int texture = baseTexture->ID;
		glBindTexture(GL_TEXTURE_2D, texture);
		//setShader(texture);
		_renderer->setShaderInfo(color, true, affectedByLight, texture, material);
		_renderer->drawRequest(model, VAO, _vertices);
	}
	void shapeWithTexture::bindBaseUVCoords()
	{
		float UVs[8] =
		{
			baseUVCoords[0].x, baseUVCoords[0].y,
			baseUVCoords[1].x, baseUVCoords[1].y,
			baseUVCoords[2].x, baseUVCoords[2].y,
			baseUVCoords[3].x, baseUVCoords[3].y
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_STATIC_DRAW);
	}
	void shapeWithTexture::modifyBaseTextureCoords(atlasCutConfig config)
	{
		int spriteWidth = 0;
		int spriteHeight = 0;
		if (config.useSize)
		{
			spriteWidth = config.spriteWidth;
			spriteHeight = config.spriteHeight;
		}
		else
		{
			spriteWidth = (int)(baseTexture->width / config.columns);
			spriteHeight = (int)(baseTexture->height / config.rows);
		}

		baseUVCoords[0].x = (spriteWidth + (spriteWidth * config.offsetX)) / baseTexture->width;		// top right
		baseUVCoords[0].y = (spriteHeight * config.offsetY) / baseTexture->height;						// top right
		baseUVCoords[1].x = (spriteWidth + (spriteWidth * config.offsetX)) / baseTexture->width; 		// bottom right
		baseUVCoords[1].y = (spriteHeight + (spriteHeight * config.offsetY)) / baseTexture->height;		// bottom right
		baseUVCoords[2].x = (spriteWidth * config.offsetX) / baseTexture->width;						// bottom left
		baseUVCoords[2].y = (spriteHeight + (spriteHeight * config.offsetY)) / baseTexture->height;		// bottom left
		baseUVCoords[3].x = (spriteWidth * config.offsetX) / baseTexture->width;						// top left 
		baseUVCoords[3].y = (spriteHeight * config.offsetY) / baseTexture->height;						// top left 

		float UVs[8] =
		{
			baseUVCoords[0].x, baseUVCoords[0].y,
			baseUVCoords[1].x, baseUVCoords[1].y,
			baseUVCoords[2].x, baseUVCoords[2].y,
			baseUVCoords[3].x, baseUVCoords[3].y
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}
	void shapeWithTexture::setTextureCoordinates(glm::vec2 coord1, glm::vec2 coord2, glm::vec2 coord3, glm::vec2 coord4)
	{
		baseUVCoords[0] = coord1;
		baseUVCoords[1] = coord2;
		baseUVCoords[2] = coord3;
		baseUVCoords[3] = coord4;
	}
	void shapeWithTexture::setTexture(renderer* render, const char* filePathImage, bool invertImage)
	{
		_renderer = render;
		float vertex[36] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	  0.0f, 1.0f, 0.0f
		};
		unsigned int indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};
		_renderer->createBaseBuffer(VAO, VBO, EBO);
		_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex), indices, sizeof(indices));
		_vertices = 6;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		float UVs[8] =
		{
			baseUVCoords[0].x, baseUVCoords[0].y,
			baseUVCoords[1].x, baseUVCoords[1].y,
			baseUVCoords[2].x, baseUVCoords[2].y,
			baseUVCoords[3].x, baseUVCoords[3].y
		};
		_renderer->createExtraBuffer(bufferPosUVs, 1);
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(3);



		baseTexture = new textureData(textureImporter::loadTexture(filePathImage, invertImage));
	}
	void shapeWithTexture::deinit()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		_renderer->deleteExtraBuffer(bufferPosUVs, 1);
		glDeleteTextures(1, &baseTexture->ID);
		delete baseTexture;
	}
}
