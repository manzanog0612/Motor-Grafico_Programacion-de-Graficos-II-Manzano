#include "baseGame.h"

#include "glew.h"
#include "glfw3.h"

namespace engine
{
    baseGame::baseGame()
    {
        currentWindow = NULL;
        currentRenderer = NULL;
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

        if (!currentWindow->getGLFWwindow())
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
    void baseGame::play()
    {
        init();
        while(!windowExitEvent())
        {
            currentRenderer->draw();
            update();
            glfwPollEvents();
        }
        deinit();
    }
    bool baseGame::windowExitEvent()
    {
        return glfwWindowShouldClose(currentWindow->getGLFWwindow());
    }
}