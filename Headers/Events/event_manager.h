#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include "../common.h"

class EventManager
{
    private:
        GLFWwindow* window;

    public:
        EventManager(GLFWwindow* window) 
        {
            this->window = window;
        }

        glm::dvec2 GetCursorPosition()
        {
            glm::dvec2 cursorPosition;
            glfwGetCursorPos(
                this->window, 
                &cursorPosition.x,
                &cursorPosition.y
            );

            return cursorPosition;
        }

        bool GetKey(int keyCode)
        {
            int state = glfwGetKey(this->window, keyCode);
            return state == GLFW_PRESS;
        }
};

#endif