#include "baseGame.h"

#include "glew.h"
#include "glfw3.h"
#include "window.h"
#include "renderer.h"
#include "input.h"

namespace engine
{
    baseGame::baseGame()
    {
        currentWindow = NULL;
        currentRenderer = NULL;
        currentInput = NULL;
    }
    baseGame::~baseGame()
    {
        delete currentWindow;
        delete currentRenderer;
        delete currentInput;
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

        currentInput = new input(currentWindow);

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

    bool baseGame::isKeyPressed(int keycode)
    {
        return currentInput->isKeyPressed(keycode, currentWindow);
    }
    bool baseGame::isKeyDown(int keycode)
    {
        return currentInput->isKeyDown(keycode, currentWindow);
    }
}