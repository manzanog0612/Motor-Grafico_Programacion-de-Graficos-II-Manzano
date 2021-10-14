#pragma once
#include "exports.h"
#include "window.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{

	class ENGINE_API renderer
	{
	public:
		renderer();
		renderer(window* window);
		~renderer();
		void setCurrentWindow(window* window);
		void bindRequest(unsigned int &VAO, unsigned int& VBO, unsigned int& EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices);
		void drawRequest(glm::mat4 model, unsigned int VAO, unsigned int vertices, unsigned int usedShaderID);
		void unbindRequest(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void startDraw();
		void endDraw();
		void setClearColor(glm::vec4 color);
		void setViewMatrix(glm::mat4 viewMatrix);
		void setProjectionMatrix(glm::mat4 projectionMatrix);
		window* getCurrentWindow();

		//TODO Pensar mejor implementacion, probablemente materiales
		Shader textureShader = Shader("../src/Motor/Shaders/TextureVertex.shader", "../src/Motor/Shaders/TextureFragment.shader");
		Shader solidShader = Shader("../src/Motor/Shaders/SolidVertex.shader", "../src/Motor/Shaders/SolidFragment.shader");

	private:
		float lastTime = 0;
		window* currentWindow;
		glm::vec4 clearColor;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}
