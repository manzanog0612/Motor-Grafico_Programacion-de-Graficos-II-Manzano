#include "renderer.h"
#include "light.h"

#include "glew.h"
#include "glfw3.h"

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
		viewMatrix = glm::mat4();
		projectionMatrix = glm::mat4();
		clearColor = glm::vec4(0, 0, 0, 1);
	}
	renderer::renderer(window* window)
	{
		clearColor = glm::vec4(0, 0, 0, 1);

		currentWindow = window;

		viewMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::mat4(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void renderer::endDraw()
	{
		glfwSwapBuffers(currentWindow->getGLFWwindow());
	}

	void renderer::setAmbientLight(float ambient)
	{
		ambientLight = ambient;
	}

	void renderer::setShaderInfo(glm::vec4 color, bool usesTexture, bool affectedByLight, unsigned int texture, MATERIAL material)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shaderPro.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shaderPro.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		unsigned int usesTextureLoc = glGetUniformLocation(shaderPro.ID, "usesTexture");
		glUniform1i(usesTextureLoc, usesTexture);

		unsigned int affectedByLightLoc = glGetUniformLocation(shaderPro.ID, "affectedByLight");
		glUniform1i(affectedByLightLoc, affectedByLight);		

		unsigned int usesTexLoc = glGetUniformLocation(shaderPro.ID, "usesTex");
		glUniform1i(usesTexLoc, usesTexture);
		
		if (usesTexture)
		{
			unsigned int textureLoc = glGetUniformLocation(shaderPro.ID, "ourTexture");
			glUniform1f(textureLoc, (GLfloat)texture);
		}

		if (affectedByLight)
		{
			Material materialValue = GetMaterialData(material);
			unsigned int materialLoc = glGetUniformLocation(shaderPro.ID, "material.diffuse");
			glUniform1i(materialLoc, materialValue.diffuse);

			materialLoc = glGetUniformLocation(shaderPro.ID, "material.specular");
			glUniform1i(materialLoc, materialValue.specular);

			materialLoc = glGetUniformLocation(shaderPro.ID, "material.shininess");
			glUniform1fv(materialLoc, 1, &(materialValue.shininess));
		}
	}

	void renderer::drawRequest(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices)
	{
		unsigned int modelLoc = glGetUniformLocation(shaderPro.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(shaderPro.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(shaderPro.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	}

	void renderer::processLight(glm::vec3 lightColor, glm::vec3 lightPos, Light light)
	{
		unsigned int lightColorLoc = glGetUniformLocation(shaderPro.ID, "lightColor");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

		unsigned int ambientStengthLoc = glGetUniformLocation(shaderPro.ID, "ambientStrength");
		glUniform1fv(ambientStengthLoc, 1, &(ambientLight));

		unsigned int lightPosLoc = glGetUniformLocation(shaderPro.ID, "lightPos");
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));


		unsigned int lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "light.ambient");
		glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light.ambient));

		unsigned int lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "light.diffuse");
		glUniform3fv(lighDiffusetLoc, 1, glm::value_ptr(light.diffuse));

		unsigned int lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "light.specular");
		glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light.specular));
	}
	void renderer::createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}
	void renderer::createExtraBuffer(unsigned int& buffer, int size)
	{
		glGenBuffers(size, &buffer);
	}
	void renderer::bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
	}
	void renderer::bindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, bufferType);
	}
	void renderer::deleteBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	void renderer::deleteExtraBuffer(unsigned int& buffer, int size)
	{
		glDeleteBuffers(size, &buffer);
	}
	void renderer::setClearColor(glm::vec4 color)
	{
		clearColor = color;
	}
	void renderer::setViewMatrix(glm::mat4 viewMatrix)
	{
		this->viewMatrix = viewMatrix;
	}
	void renderer::setViewPosition(glm::vec3 viewPos)
	{
		unsigned int viewPosLoc = glGetUniformLocation(shaderPro.ID, "viewPos");
		glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));
	}
	void renderer::setProjectionMatrix(glm::mat4 projectionMatrix)
	{
		this->projectionMatrix = projectionMatrix;
	}
	window* renderer::getCurrentWindow()
	{
		return currentWindow;
	}
	Material renderer::GetMaterialData(MATERIAL material)
	{
		Material mat;

		switch (material)
		{
		case MATERIAL::EMERALD:
			mat = Material(glm::vec3(0.0215f, 0.0215f, 0.0215f), 0, 0, 0.6f * 100);
			break;
		case MATERIAL::PEARL:
			mat = Material(glm::vec3(0.25f, 0.20725f, 0.20725f), 0, 0, 0.088f * 100);
			break;
		case MATERIAL::BRONZE:
			mat = Material(glm::vec3(0.2125f, 0.1275f, 0.054f), 0, 0, 0.2f * 100);
			break;
		case MATERIAL::GOLD:
			mat = Material(glm::vec3(0.24725f, 0.1995f, 0.0745f), 0, 0, 0.4f * 100);
			break;
		case MATERIAL::CYAN_PLASTIC:
			mat = Material(glm::vec3(0.0f, 0.1f, 0.06f), 0, 0, .25f * 10);
			break;
		case MATERIAL::RED_PLASTIC:
			mat = Material(glm::vec3(0.0f, 0.0f, 0.0f), 0, 0, .25f * 10);
			break;
		case MATERIAL::GREEN_RUBBER:
			mat = Material(glm::vec3(0.0f, 0.5f, 0.0f), 0, 0, .078125f * 50);
			break;
		case MATERIAL::YELLOW_RUBBER:
			mat = Material(glm::vec3(0.05f, 0.05f, 0.0f), 0, 0, .078125f * 50);
			break;
		default:
			break;
		}

		return mat;
	}
}