#ifndef _WINDOW_H
#define _WINDOW_H

#include "../Utility/disposable.h"
#include "../common.h"

class Window : public Disposable
{
    private:
        float frameFrequency;
        GLFWwindow* window;

    public:
        void (*onResize)(GLFWwindow*, int, int) = 0;

        Window(int width, int height, const char* title, int fpsCap = 30);

        void Free();

        void Show(std::function<void(Window*, float)> mainLoop);

        void SetFpsCap(int fpsCap) { this->frameFrequency = 1.0f / (float) fpsCap; }

        glm::vec2 Size() 
        { 
            glm::ivec2 size = glm::ivec2(0, 0);
            glfwGetWindowSize(this->window, &size.x, &size.y);
            return size;
        }
};

#endif