#include "../Headers/Graphics/window.h"

Window::Window(int width, int height, const char* title, int fpsCap)
{
    if (glfwInit() == GLFW_FALSE)
        throw new std::runtime_error("GLFW: initialization failed!");

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    this->frameFrequency = 1.0f / (float) fpsCap;

    if (this->window == nullptr)
        throw std::runtime_error("GLFW: failed to create GLFW window!");
    
    glfwMakeContextCurrent(this->window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW: initialization failed");

    glViewport(0, 0, width, height);
    glfwSetWindowSizeCallback(this->window, this->onResize);
}

void Window::Show(void (*mainLoop)(Window*, float))
{
    while (!glfwWindowShouldClose(this->window))
    {
        float dt = glfwGetTime();
        if (dt >= this->frameFrequency)
        {
            glfwSetTime(0);
            mainLoop(this, dt);

            glfwSwapBuffers(this->window);
        }

        glfwPollEvents();
    }
}

void Window::Free()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}