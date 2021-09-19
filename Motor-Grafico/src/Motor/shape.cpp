#include "shape.h"

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
				 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f
			};
			indices = new unsigned int[3]
			{
				0, 1, 2
			};
			_renderer->bindRequest(VAO, VBO, EBO, vertex, indices);
			_vertices = sizeof(indices);

			delete[] vertex;
			delete[] indices;
		}
		else if(vert == 4)
		{
			vertex = new float[24]
			{
				0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f
			};
			indices = new unsigned int[6]
			{
				0, 1, 2,
				1, 2, 3
			};
			_renderer->bindRequest(VAO, VBO, EBO, vertex, indices);
			_vertices = sizeof(indices);

			delete[] vertex;
			delete[] indices;
		}
		else
		{
			std::cout << "Vertices amount not implemented" << std::endl;
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