#pragma once
#include "glew.h"
#include "glfw3.h"
#include <string>
#include <iostream>

class window
{
public:
	window(int width, int height, std::string windowName);
	~window();
	void init();
	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();

private:
	GLFWwindow* _window;
	int _width;
	int _height;
};
