#pragma once
#include "exports.h"
#include "window.h"
#include "shader.h"

namespace engine
{

	class ENGINE_API renderer
	{
	public:
		renderer();
		renderer(window* window);
		~renderer();
		void setCurrentWindow(window* window);
		void draw();

	private:
		float lastTime = 0;
		window* currentWindow;
		Shader solidShader = Shader("../src/Motor/Shaders/SolidVertex.shader", "../src/Motor/Shaders/SolidFragment.shader");
		unsigned int VBO, VAO, EBO;
		//glm::mat4 viewMatrix;
		//glm::mat4 cameraMatrix;
	};
}
