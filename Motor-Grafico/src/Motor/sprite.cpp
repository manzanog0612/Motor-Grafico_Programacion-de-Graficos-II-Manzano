#include "textureImporter.h"
#include "renderer.h"
#include "animation.h"
#include "sprite.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	sprite::sprite(renderer* render, const char* filePathImage, bool invertImage)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;

		float vertex[24] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f
		};
		unsigned int indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};
		_renderer->createBaseBuffer(VAO, VBO, EBO);
		_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) , indices, sizeof(indices));
		_vertices = 6;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		float UVs[8] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
		_renderer->createExtraBuffer(bufferPosUVs, 1);
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);

		baseTexture = new textureData(textureImporter::loadTexture(filePathImage, invertImage));
	}
	sprite::~sprite()
	{
		delete baseTexture;
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		_renderer->deleteExtraBuffer(bufferPosUVs, 1);
		glDeleteTextures(1, &baseTexture->ID);
		for (int i = 0; i < animations.size(); i++)
		{
			delete animations[i];
		}
	}
	void sprite::draw()
	{
		_renderer->textureShader.use();
		unsigned int texture = getCurrentTextureIDToDraw();
		glBindTexture(GL_TEXTURE_2D, texture);
		setShader(texture);
		_renderer->drawRequest(model, VAO, _vertices, _renderer->textureShader.ID);
	}
	void sprite::setShader(unsigned int texture)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(_renderer->textureShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->textureShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		unsigned int textureLoc = glGetUniformLocation(_renderer->textureShader.ID, "ourTexture");
		glUniform1f(textureLoc, texture);
	}
	unsigned int sprite::getCurrentTextureIDToDraw()
	{
		for (int i = 0; i < animations.size(); i++)
		{
			if(animations[i]->isPlaying())
			{
				animations[i]->update();
				bindAnimationTexture(i);
				lastAnimationIndex = i;
				return animations[i]->getTextureID();
			}
		}
		if (animations.size() == 0) bindBaseTexture();
		else bindAnimationTexture(lastAnimationIndex);
		return baseTexture->ID;
	}
	void sprite::bindAnimationTexture(int i)
	{
		glm::vec2* uv = animations[i]->getCurrentFramesCoordinates();
		float UVs[8] =
		{
			uv[0].x, uv[0].y, // top right
			uv[1].x, uv[1].y, // bottom right
			uv[2].x, uv[2].y, // bottom left
			uv[3].x, uv[3].y, // top left 
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}
	void sprite::bindBaseTexture()
	{
		float UVs[8] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}
	textureData* sprite::createAnimationAtlas(const char* AtlasFilepath, bool invertImage)
	{
		return new textureData(textureImporter::loadTexture(AtlasFilepath, invertImage));
	}
	void sprite::deleteAnimationAtlas(textureData* atlas)
	{
		delete atlas;
	}
	int sprite::createAnimation(textureData* animationAtlasData, int columns, int rows)
	{
		animation* anim = new animation();
		anim->setAnimation(animationAtlasData, columns, rows);
		animations.push_back(anim);
		return animations.size() - 1;
	}
	int sprite::createAnimation(textureData* animationAtlasData, atlasCutConfig config)
	{
		animation* anim = new animation();
		anim->setAnimation(animationAtlasData, config);
		animations.push_back(anim);
		return animations.size() - 1;
	}
	void sprite::playAnimation(int animationID)
	{
		if (!animations[animationID]->isPlaying())
		{
			for (int i = 0; i < animations.size(); i++)
			{
				animations[i]->stop();
			}
			animations[animationID]->play();
		}
	}
	void sprite::stopAnimation(int animationID)
	{
		animations[animationID]->stop();
	}
	void sprite::stopAllAnimations()
	{
		for (int i = 0; i < animations.size(); i++)
		{
			animations[i]->stop();
		}
	}
	void sprite::setAnimationSpeed(int animationID, float speed)
	{
		animations[animationID]->setAnimationSpeed(speed);
	}
}
