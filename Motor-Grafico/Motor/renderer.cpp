#include "renderer.h"

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
		buffer = 0;
	}
	renderer::renderer(window* window)
	{
		currentWindow = window;

		float positions[6] =
		{
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f,
		};

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	}

	renderer::~renderer()
	{

	}

	void renderer::setCurrentWindow(window* window)
	{
		currentWindow = window;
	}

	void renderer::draw()
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(currentWindow->getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

}