#ifndef _WINDOW_H
#define _WINDOW_H

#include "../common.h"

class Window
{
    private:
        float frameFrequency;
        GLFWwindow* window;

    public:
        void (*onResize)(GLFWwindow*, int, int) = 0;

        Window(int width, int height, const char* title, int fpsCap = 30);

        void Free();

        void Show(void (*mainLoop)(Window*, float));

        void SetFpsCap(int fpsCap) { this->frameFrequency = 1.0f / (float) fpsCap; }
};

#endif