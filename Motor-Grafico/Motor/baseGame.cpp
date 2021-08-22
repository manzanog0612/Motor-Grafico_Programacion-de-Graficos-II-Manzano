#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "baseGame.h"

namespace engine
{
    baseGame::baseGame()
    {
        currentWindow = NULL;
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

        return true;
    }
    void baseGame::deinit()
    {
        glfwTerminate();
    }
    void baseGame::update()
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(currentWindow->getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
    bool baseGame::windowExitEvent()
    {
        return glfwWindowShouldClose(currentWindow->getWindow());
    }
}