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
		void drawRequest(glm::mat4 model, unsigned int id, unsigned int vertices);
		void startDraw();
		void endDraw();

	private:
		float lastTime = 0;
		window* currentWindow;
		Shader solidShader = Shader("../src/Motor/Shaders/SolidVertex.shader", "../src/Motor/Shaders/SolidFragment.shader");
		unsigned int VBO, VAO, EBO, VAO2;
		//glm::mat4 viewMatrix;
		//glm::mat4 cameraMatrix;
	};
}
