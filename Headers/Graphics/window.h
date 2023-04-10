#ifndef _WINDOW_H
#define _WINDOW_H

#include "../Utility/disposable.h"
#include "../common.h"

class Window : public Disposable
{
    private:
        GLFWwindow* window;
        std::string title;

        float frameFrequency;
        bool showFps;

    public:
        void (*onResize)(GLFWwindow*, int, int) = 0;

        Window(int width, int height, const char* title, int fpsCap = 30);

        void Dispose();

        void Show(std::function<void(Window*, float)> mainLoop);

        void SetTitle(const char* title) { glfwSetWindowTitle(this->window, title); }

        void SetFpsCap(int fpsCap) { this->frameFrequency = 1.0f / (float) fpsCap; }

        void ShowFpsCounter(bool value) { this->showFps = value; }

        glm::vec2 Size() 
        { 
            glm::ivec2 size = glm::ivec2(0, 0);
            glfwGetWindowSize(this->window, &size.x, &size.y);
            return size;
        }
};

#endif