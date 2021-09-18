#include "baseGame.h"

#include "glew.h"
#include "glfw3.h"
#include "window.h"
#include "renderer.h"

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
        delete currentRenderer;
    }
    bool baseGame::init_Internal()
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
        init();

        return true;
    }
    void baseGame::deinit_Internal()
    {
        deInit();
        glfwTerminate();
    }
    void baseGame::play()
    {
        init_Internal();
        while(!windowExitEvent())
        {
            currentRenderer->startDraw();
            draw();
            currentRenderer->endDraw();
            glfwPollEvents();
            update();
        }
        deinit_Internal();
    }
    bool baseGame::windowExitEvent()
    {
        return glfwWindowShouldClose(currentWindow->getGLFWwindow());
    }
}