#include "glfw3.h"
#include "window.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    window* currentWindow = new window(800, 600, "Hello World");

    if(!currentWindow->getWindow())
    {
        glfwTerminate();
        return -1;
        delete currentWindow;
    }

    currentWindow->init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(currentWindow->getWindow()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(currentWindow->getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    delete currentWindow;
    return 0;
}