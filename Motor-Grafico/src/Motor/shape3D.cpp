#include "shape3D.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	shape3D::shape3D(renderer* render, shapeType shape)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;

		float* vertex;
		unsigned int* indices;

		switch (shape)
		{
		case engine::cube:
			vertex = new float[18]
			{
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
			};
			indices = new unsigned int[3]
			{
				0, 1, 2
			};
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 18, indices, sizeof(indices) * 3);
			_vertices = 3;

			delete[] vertex;
			delete[] indices;
			break;
		case engine::other:
			break;
		default:
			std::cout << "3D shape type not implemented." << std::endl;
			return;
			break;
		}
		if(vert == 3)
		{
			vertex = new float[18]
			{
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
			};
			indices = new unsigned int[3]
			{
				0, 1, 2
			};
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 18, indices, sizeof(indices) * 3);
			_vertices = 3;

			delete[] vertex;
			delete[] indices;
		}
		else if(vert == 4)
		{
			vertex = new float[24]
			{
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
			};
			indices = new unsigned int[6]
			{
				0, 1, 3,
				1, 2, 3
			};
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 24, indices, sizeof(indices) * 6);
			_vertices = 6;

			delete[] vertex;
			delete[] indices;
		}
		else
		{
			
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

	}

	shape3D::~shape3D()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
	}

	void shape3D::draw()
	{
		_renderer->solidShader.use();
		setShader();
		_renderer->drawRequest(model, VAO, _vertices, _renderer->solidShader.ID);
	}

	void shape3D::setShader()
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(_renderer->solidShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->solidShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));
	}
}