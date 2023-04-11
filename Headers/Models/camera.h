#ifndef _CAMERA_H
#define _CAMERA_H

#include "../Scene./transform.h"
#include "../common.h"

class Camera
{
    public:
        Transform transform;
        glm::vec2 nearPlaneSize;
        float nearPlaneDistance;

        Camera(glm::vec2 nearPlaneSize, float nearPlaneDistance)
        {
            this->transform = Transform();
            this->nearPlaneSize = nearPlaneSize;
            this->nearPlaneDistance = nearPlaneDistance;
        }
};

#endif