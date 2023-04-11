#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "./geometry.h"

class Sphere : public Geometry
{
    public:
        float radius;

        Sphere(glm::vec3 position, float radius, Material material) : Geometry(position, material)
        {
            this->radius = radius;
        }
};

class Plane : public Geometry
{
    public:
        glm::vec3 size;

        Plane(glm::vec3 position, glm::vec3 size, Material material) : Geometry(position, material)
        {
            this->size = size;
        }
};

#endif