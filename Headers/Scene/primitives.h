#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "./geometry.h"

class Sphere : public Geometry
{
    public:
        Sphere(glm::vec3 position, float radius, Material material) : Geometry(position, material)
        {
            this->transform.Scale(glm::vec3(radius));
        }
};

class Plane : public Geometry
{
    public:
        Plane(glm::vec3 position, glm::vec3 size, Material material) : Geometry(position, material)
        {
            this->transform.Scale(size);
        }
};

#endif