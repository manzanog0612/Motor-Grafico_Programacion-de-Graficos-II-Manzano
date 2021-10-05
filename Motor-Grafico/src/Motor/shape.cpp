#include "shape.h"
#include "renderer.h"
#include <iostream>

namespace engine
{
	shape::shape(unsigned int vert)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;

		float* vertex;
		unsigned int* indices;

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
			_renderer->bindRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 18, indices, sizeof(indices) * 3);
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
			_renderer->bindRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 24, indices, sizeof(indices) * 6);
			_vertices = 6;

			delete[] vertex;
			delete[] indices;
		}
		else
		{
			std::cout << vert << " Vertices amount not implemented." << std::endl;
			return;
		}
	}

	shape::~shape()
	{
		_renderer->unbindRequest(VAO, VBO, EBO);
	}

	void shape::draw()
	{
		_renderer->drawRequest(model, color, VAO, _vertices);
	}
}