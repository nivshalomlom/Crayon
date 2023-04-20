#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "../common.h"

class Transform
{
    private:
        glm::mat4 localToWorld;

    public:
        Transform(glm::vec3 position = glm::vec3(0), glm::vec3 lookkAt = glm::vec3(0, 0, 1), glm::vec3 up = glm::vec3(0, 1, 0))
        {
            this->localToWorld = glm::translate(glm::identity<glm::mat4>(), position);
        }

        Transform(glm::mat4 transform)
        {
            this->localToWorld = transform;
        }

        glm::vec3 Position();

        glm::vec3 Up();

        glm::vec3 Forward();

        glm::vec3 Right();

        void Scale(glm::vec3 scale) { this->localToWorld = glm::scale(this->localToWorld, scale); }

        void LookAt(glm::vec3 position) { this->localToWorld *= glm::lookAt(this->Position(), position, this->Up()); }

        void Rotate(glm::vec3 axis, float angle) { this->localToWorld = glm::rotate(this->localToWorld, glm::radians(angle), axis); };

        void Translate(glm::vec3 translation) { this->localToWorld = glm::translate(this->localToWorld, translation); }
};

#endif