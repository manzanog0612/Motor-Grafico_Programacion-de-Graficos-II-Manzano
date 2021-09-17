#include "renderer.h"

#include "glew.h"
#include "glfw3.h"

namespace engine
{

	renderer::renderer()
	{
		currentWindow = NULL;
		VAO = 0;
		VBO = 0;
		EBO = 0;
		//viewMatrix = glm::mat4();
		//cameraMatrix = glm::mat4();
	}
	renderer::renderer(window* window)
	{
		currentWindow = window;

		//viewMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, 0.0f));
		//cameraMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

		float vertices[] = 
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
		};
		unsigned int indices[] = 
		{  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0); 
		glEnableVertexAttribArray(1);


		float vertices2[] =
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // bottom right
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // bottom left
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f   // top left 
		};
		unsigned int indices2[] =
		{  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glGenVertexArrays(1, &VAO2);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO2);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


	}
	renderer::~renderer()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	void renderer::setCurrentWindow(window* window)
	{
		currentWindow = window;
	}
	void renderer::startDraw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0, 0, 0, 1);

		solidShader.use();

		glm::mat4 matrixTRS = glm::mat4(1.0f);
		float moveAmount = sin(glfwGetTime());
		matrixTRS = glm::translate(matrixTRS, glm::vec3(moveAmount, moveAmount, 0.0f));
		matrixTRS = glm::rotate(matrixTRS, (float)glfwGetTime() * 5, glm::vec3(0.0f, 0.0f, 1.0f));
		matrixTRS = glm::scale(matrixTRS, glm::vec3(0.25f, .25f, .25f));

		//matrixTRS *= viewMatrix * cameraMatrix;
		unsigned int transformLoc = glGetUniformLocation(solidShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrixTRS));

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		matrixTRS = glm::mat4(1.0f);
		matrixTRS = glm::translate(matrixTRS, glm::vec3(0.0f, -0.45f, 0.0f));
		matrixTRS = glm::rotate(matrixTRS, (float)glfwGetTime() * -1, glm::vec3(0.0f, 0.0f, 1.0f));
		float scaleAmount = sin(glfwGetTime());
		matrixTRS = glm::scale(matrixTRS, glm::vec3(scaleAmount, scaleAmount, scaleAmount));

		//matrixTRS *= viewMatrix * cameraMatrix;
		transformLoc = glGetUniformLocation(solidShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrixTRS));

		glBindVertexArray(VAO2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		matrixTRS = glm::mat4(1.0f);
		matrixTRS = glm::translate(matrixTRS, glm::vec3(-0.3f, 0.5f, 0.0f));
		matrixTRS = glm::rotate(matrixTRS, (float)glfwGetTime() * -1, glm::vec3(1.0f, 1.0f, 0.0f));
		matrixTRS = glm::scale(matrixTRS, glm::vec3(.5f, .5f, .5f));

		//matrixTRS *= viewMatrix * cameraMatrix;
		transformLoc = glGetUniformLocation(solidShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrixTRS));

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	void renderer::endDraw()
	{
		glfwSwapBuffers(currentWindow->getGLFWwindow());
	}
	void renderer::drawRequest(glm::mat4 model, unsigned int id, unsigned int vertices)
	{

	}

}