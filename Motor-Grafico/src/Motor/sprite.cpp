#include "sprite.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"
#include "stb_image.h"

namespace engine
{
	sprite::sprite(renderer* render, const char* filePathImage)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		textureID = 0;
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

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePathImage, &textureWidth, &textureHeight, &numberOfColorChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	sprite::~sprite()
	{
		_renderer->unbindRequest(VAO, VBO, EBO);
	}

	void sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		_renderer->textureShader.use();
		setShader();
		_renderer->drawRequest(model, VAO, _vertices, _renderer->textureShader.ID);
	}

	void sprite::setShader()
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(_renderer->textureShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->textureShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		unsigned int textureLoc = glGetUniformLocation(_renderer->textureShader.ID, "ourTexture"); //TODO Chequear si es correcto esta forma de pasar la textura
		glUniform1f(textureLoc, textureID);

	}
}
