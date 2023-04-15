#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "../common.h"

class Transform
{
    private:
        glm::mat4 transform;

    public:
        Transform(glm::vec3 position = glm::vec3(0), glm::vec3 lookkAt = glm::vec3(0, 0, 1), glm::vec3 up = glm::vec3(0, 1, 0))
        {
            this->transform = glm::translate(glm::identity<glm::mat4>(), position);
        }

        Transform(glm::mat4 transform)
        {
            this->transform = transform;
        }

        glm::vec3 Position();

        glm::vec3 Up();

        glm::vec3 Forward();

        glm::vec3 Right();

        void Scale(glm::vec3 scale) { this->transform = glm::scale(this->transform, scale); }

        void LookAt(glm::vec3 position) { this->transform *= glm::lookAt(this->Position(), -position, this->Up()); }

        void Rotate(glm::vec3 axis, float angle) { this->transform = glm::rotate(this->transform, glm::radians(angle), axis); };

        void Translate(glm::vec3 translation) { this->transform = glm::translate(this->transform, translation); }
};

#endif