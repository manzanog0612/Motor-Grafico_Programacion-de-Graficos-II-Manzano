#include "sprite.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"
#include "textureImporter.h"

namespace engine
{
	sprite::sprite(renderer* render, const char* filePathImage)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		baseTextureID = 0;
		_renderer = render;

		float vertex[]
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f
		};
		unsigned int indices[]
		{
			0, 1, 3,
			1, 2, 3
		};
		_renderer->bindRequest(VAO, VBO, EBO, vertex, sizeof(vertex), indices, sizeof(indices));
		_vertices = 6;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		baseTextureID = textureImporter::loadTexture(filePathImage);
	}

	sprite::~sprite()
	{
		_renderer->unbindRequest(VAO, VBO, EBO);
	}

	void sprite::draw()
	{
		_renderer->textureShader.use();
		unsigned int texture = getCurrentTextureToDraw();
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
	unsigned int sprite::getCurrentTextureToDraw()
	{
		for (int i = 0; i < animations.size(); i++)
		{
			if(animations[i].isPlaying())
			{
				animations[i].update();
				return animations[i].getCurrentAnimationFrame();
			}
		}
		return baseTextureID;
	}

	int sprite::createAnimation(const char* firstFrameFilePathImage)
	{
		animation anim;
		unsigned int newTextureID = textureImporter::loadTexture(firstFrameFilePathImage);
		anim.addAnimationFrame(newTextureID);
		animations.push_back(anim);
		return animations.size() - 1;
	}
	void sprite::playAnimation(int animationID)
	{
		if(!animations[animationID].isPlaying()) animations[animationID].play();
	}
	void sprite::stopAnimation(int animationID)
	{
		animations[animationID].stop();
	}
	void sprite::setAnimationSpeed(int animationID, float speed)
	{
		animations[animationID].setAnimationSpeed(speed);
	}
	void sprite::addFrameToAnimation(int animationID, const char* filePathImage)
	{
		unsigned int newTextureID = textureImporter::loadTexture(filePathImage);
		animations[animationID].addAnimationFrame(newTextureID);
	}
}
