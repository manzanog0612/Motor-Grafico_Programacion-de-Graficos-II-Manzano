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
		void createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void createExtraBuffer(unsigned int& buffer, int size);
		void bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices);
		void bindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType);
		void SetShaderInfo(glm::vec4 color, bool usesTexture, bool affectedByLight, unsigned int texture);
		void drawRequest(glm::mat4 model, unsigned int VAO, unsigned int vertices);
		void deleteBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void deleteExtraBuffer(unsigned int& buffer, int size);
		void startDraw();
		void endDraw();
		void setClearColor(glm::vec4 color);
		void setViewMatrix(glm::mat4 viewMatrix);
		void setProjectionMatrix(glm::mat4 projectionMatrix);
		window* getCurrentWindow();

		//TODO Pensar mejor implementacion, probablemente materiales
		Shader shaderPro = Shader("../src/Motor/Shaders/TextureVertex.shader", "../src/Motor/Shaders/TextureFragment.shader");

	private:
		float lastTime = 0;
		window* currentWindow;
		glm::vec4 clearColor;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}
