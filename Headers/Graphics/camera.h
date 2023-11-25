#ifndef _CAMERA_H
#define _CAMERA_H

#include "../Geometry/transform.h"
#include "../common.h"

class Camera
{
    private:
        void UpdateNearPlane(float theta, float aspectRatio, float nearPlaneDistance)
        {
            float height = 2.0f * tanf(theta / 2.0f) * nearPlaneDistance;
            this->nearPlaneSize = glm::vec2(aspectRatio * height, height);
            this->nearPlaneDistance = nearPlaneDistance;
        }

    public:
        Transform transform;
        glm::vec2 nearPlaneSize;
        float nearPlaneDistance;
        GLuint frameCounter;

        Camera(glm::vec3 position = glm::vec3(0), float fov = 25.0f, float aspectRatio = 1.777, float near = 5, float far = 20)
        {
            this->transform = Transform(position);
            this->UpdateNearPlane(glm::radians(fov), aspectRatio, near);
        }

        void SetFOV(float fov)
        {
            this->UpdateNearPlane(
                fov, 
                this->nearPlaneSize.x / this->nearPlaneSize.y, 
                this->nearPlaneDistance
            );
        }

        void SetNearPlaneDistance(float distance)
        {
            float tanResult = this->nearPlaneSize.y / (2.0 * this->nearPlaneDistance);
            this->UpdateNearPlane(
                atanf(tanResult) / 2.0,
                this->nearPlaneSize.x / this->nearPlaneSize.y, 
                distance
            );
        }
};

#endif