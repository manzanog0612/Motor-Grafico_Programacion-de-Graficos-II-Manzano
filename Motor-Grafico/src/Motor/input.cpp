#include "input.h"
#include "glfw3.h"
#include "window.h"
#include <algorithm>

namespace engine
{
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	std::list<int> currentKeysDown;
	glm::vec2 mousePosition;

	input::input(window* window)
	{
		glfwSetKeyCallback(window->getGLFWwindow(), keyCallback);
		glfwSetCursorPosCallback(window->getGLFWwindow(), mouse_callback);
	}

	input::~input()
	{

	}

	bool input::isKeyPressed(int keycode, window* window)
	{
		int aux = glfwGetKey(window->getGLFWwindow(), keycode);
		return aux == GLFW_PRESS;
	}

	bool input::isKeyDown(int keycode, window* window)
	{
		std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keycode);
		if(it != currentKeysDown.end())
		{
			currentKeysDown.remove(keycode);
			return true;
		}
		return false;
	}
	glm::vec2 input::getMousePosition()
	{
		return mousePosition;
	}
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(action == GLFW_PRESS)
		{
			currentKeysDown.push_front(key);
		}
		else if(action == GLFW_RELEASE)
		{
			currentKeysDown.remove(key);
		}
	}
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePosition = glm::vec2(xpos, ypos);
	}
}