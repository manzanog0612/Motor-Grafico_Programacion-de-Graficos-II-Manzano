#include "light.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	light::light()
	{
		VAO = 0;
		VBO = 0;
		_renderer = nullptr;
	}

	light::light(renderer* render)
	{
		VAO = 0;
		VBO = 0;
		_renderer = render;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// we only need to bind to the VBO, the container's VBO's data already contains the data.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// set the vertex attribute 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	light::~light()
	{
		_renderer->deleteBaseBuffer(VAO, VBO);
	}

	void light::draw()
	{
	}

}