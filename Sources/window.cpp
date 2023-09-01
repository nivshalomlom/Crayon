#include "../Headers/Graphics/window.h"

#define TITLE_FPS_FORMAT "%s [FPS: %f]"

using namespace std;

void DisplayFPSCounter(Window* window, char* titleBuffer, const char* rawTitle, float dt, bool showFPS)
{
    if (showFPS)
    {
        sprintf(
            titleBuffer, TITLE_FPS_FORMAT, 
            rawTitle, 1.0 / dt
        );

        window->SetTitle(titleBuffer);
    }
    else
        window->SetTitle(rawTitle);
}

Window::Window(int width, int height, const char* title, int fpsCap)
{
    // Create window with OpenGL context
    if (glfwInit() == GLFW_FALSE)
        throw new std::runtime_error("GLFW: initialization failed!");

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    this->frameFrequency = 1.0f / (float) fpsCap;
    this->showFps = false;
    this->title = title;

    if (this->window == nullptr)
        throw std::runtime_error("GLFW: failed to create GLFW window!");
    
    glfwMakeContextCurrent(this->window);

    // Configure GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW: initialization failed");

    glViewport(0, 0, width, height);
    
    // Event handling
    glfwSetWindowSizeCallback(this->window, this->onResize);
}

void Window::Show(std::function<void(Window*, Time)> mainLoop)
{
    char titleBuffer[100];
    Time time = Time();

    while (!glfwWindowShouldClose(this->window))
    {
        float dt = glfwGetTime();
        if (dt >= this->frameFrequency)
        {
            DisplayFPSCounter(this, titleBuffer, this->title.c_str(), dt, this->showFps);
            time.deltaTime = dt;

            glfwSetTime(0);
            mainLoop(this, time);

            time.elapsedTime += dt;
            glfwSwapBuffers(this->window);
        }

        glfwPollEvents();
    }
}

void Window::Dispose()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}