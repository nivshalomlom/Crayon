#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "./geometry.h"

class Sphere : public Geometry
{
    public:
        float radius;

        Sphere(Material material, float radius) : Geometry(material)
        {
            this->radius = radius;
        }
};

class Plane : public Geometry
{
    public:
        glm::vec3 size;

        Plane(Material material, glm::vec3 size) : Geometry(material)
        {
            this->size = size;
        }
};

#endif