#include "baseGame.h"

#include "glew.h"
#include "glfw3.h"

namespace engine
{
    baseGame::baseGame()
    {
        currentWindow = NULL;
        currentRenderer = NULL;
        windowShouldClose = false;
    }
    baseGame::~baseGame()
    {
        delete currentWindow;
    }
    bool baseGame::init()
    {
        if (!glfwInit())
            return false;

        currentWindow = new window(800, 600, "Hello World");

        if (!currentWindow->getWindow())
        {
            glfwTerminate();
            return false;
            delete currentWindow;
        }

        currentWindow->init();

        currentRenderer = new renderer(currentWindow);

        return true;
    }
    void baseGame::deinit()
    {
        glfwTerminate();
    }
    void baseGame::update()
    {
        currentRenderer->draw();
        glfwPollEvents();
    }
    bool baseGame::windowExitEvent()
    {
        return glfwWindowShouldClose(currentWindow->getWindow());
    }
}