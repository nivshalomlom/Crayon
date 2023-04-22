#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "../common.h"

class Transform
{
    private:
        glm::mat4 localToWorld;
        glm::mat4 worldToLocal;

        void UpdateTransform(glm::mat4 transform)
        {
            this->localToWorld = transform;
            this->worldToLocal = glm::inverse(transform);
        }

    public:
        Transform(glm::vec3 position = glm::vec3(0))
        {
            this->localToWorld = glm::translate(glm::identity<glm::mat4>(), position);
            this->worldToLocal = glm::inverse(this->localToWorld);
        }

        Transform(glm::mat4 transform)
        {
            this->localToWorld = transform;
        }

        glm::vec3 Position();

        glm::vec3 Up();

        glm::vec3 Forward();

        glm::vec3 Right();

        void Scale(glm::vec3 scale) { this->UpdateTransform(glm::scale(this->localToWorld, scale)); }

        void LookAt(glm::vec3 position) { this->UpdateTransform(this->localToWorld * glm::lookAt(this->Position(), position, this->Up())); }

        void Rotate(glm::vec3 axis, float angle) { this->UpdateTransform(glm::rotate(this->localToWorld, glm::radians(angle), axis)); };

        void Translate(glm::vec3 translation) { this->UpdateTransform(glm::translate(this->localToWorld, translation)); }
};

#endif