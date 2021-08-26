#include "renderer.h"

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
	}
	renderer::renderer(window* window)
	{
		currentWindow = window;
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

		/* Swap front and back buffers */
		glfwSwapBuffers(currentWindow->getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

}