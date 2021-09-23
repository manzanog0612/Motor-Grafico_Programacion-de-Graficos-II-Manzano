#include "renderer.h"

#include "glew.h"
#include "glfw3.h"

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
		viewMatrix = glm::mat4();
		cameraMatrix = glm::mat4();
		clearColor = glm::vec4(0, 0, 0, 1);
	}
	renderer::renderer(window* window)
	{

		clearColor = glm::vec4(0, 0, 0, 1);

		currentWindow = window;

		viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		cameraMatrix = glm::mat4(1.0f);
		//cameraMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	}
	renderer::~renderer()
	{

	}
	void renderer::setCurrentWindow(window* window)
	{
		currentWindow = window;
	}
	void renderer::startDraw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

		solidShader.use();
	}
	void renderer::endDraw()
	{
		glfwSwapBuffers(currentWindow->getGLFWwindow());
	}
	void renderer::drawRequest(glm::mat4 modelMatrix, glm::vec4 color, unsigned int VAO, unsigned int vertices)
	{
		unsigned int modelLoc = glGetUniformLocation(solidShader.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(solidShader.ID, "view");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(solidShader.ID, "projection");
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

		glm::vec3 newColor = glm::vec3(color.a, color.b, color.g);
		unsigned int colorLoc = glGetUniformLocation(solidShader.ID, "color");
		//glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(solidShader.ID, "a");
		//glUniform1fv(alphaLoc, 1, &(color.a));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	}
	void renderer::bindRequest(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, float vertices[], unsigned int indices[])
	{


		float ver[24]
		{
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
		};
		unsigned int ind[6]
		{
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	void renderer::unbindRequest(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	void renderer::setClearColor(float r, float g, float b, float a)
	{
		clearColor = glm::vec4(r, g, b, a);
	}
}