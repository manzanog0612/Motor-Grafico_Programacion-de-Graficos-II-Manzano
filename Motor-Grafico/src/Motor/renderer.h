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
		void bindRequest(unsigned int &VAO, unsigned int& VBO, unsigned int& EBO, float vertices[], unsigned int indices[]);
		void drawRequest(glm::mat4 model, glm::vec4 color, unsigned int VAO, unsigned int vertices);
		void unbindRequest(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void startDraw();
		void endDraw();
		void setClearColor(float r, float g, float b, float a);

	private:
		float lastTime = 0;
		window* currentWindow;
		Shader solidShader = Shader("../src/Motor/Shaders/SolidVertex.shader", "../src/Motor/Shaders/SolidFragment.shader");
		glm::vec4 clearColor;
		glm::mat4 viewMatrix;
		glm::mat4 cameraMatrix;
	};
}
