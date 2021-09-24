#include "baseGame.h"

#include "glew.h"
#include "glfw3.h"
#include "window.h"
#include "renderer.h"
#include "input.h"
#include <random>

namespace engine
{
    baseGame::baseGame()
    {
        currentWindow = NULL;
        currentRenderer = NULL;
        currentInput = NULL;
        currentTimer = NULL;
    }
    baseGame::~baseGame()
    {
        delete currentWindow;
        delete currentRenderer;
        delete currentInput;
    }
    bool baseGame::init_Internal(int windowSizeX, int windowSizeY, const char* windowName)
    {
        if (!glfwInit())
            return false;

        currentWindow = new window(windowSizeX, windowSizeY, windowName);
        if (!currentWindow->getGLFWwindow())
        {
            glfwTerminate();
            delete currentWindow;
            return false;
        }
        currentWindow->init();

        currentRenderer = new renderer(currentWindow);

        currentInput = new input(currentWindow);

        currentTimer = new time();

        return true;
    }
    void baseGame::deinit_Internal()
    {
        glfwTerminate();
    }
    void baseGame::play(int windowSizeX, int windowSizeY, const char* windowName)
    {
        if(init_Internal(windowSizeX, windowSizeY, windowName))
        {
            init();
            while (!windowExitEvent())
            {
                glfwPollEvents();
                time::updateDeltaTime(getCurrentTime());
                update();
                currentRenderer->startDraw();
                draw();
                currentRenderer->endDraw();
            }
            deInit();
            deinit_Internal();
        }
    }
    void baseGame::changeClearColor(float r, float g, float b, float a)
    {
        currentRenderer->setClearColor(r, g, b, a);
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
    double baseGame::getCurrentTime()
    {
        return glfwGetTime();
    }
    float baseGame::getRandomNumber(float min, float max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(mt);
    }
}