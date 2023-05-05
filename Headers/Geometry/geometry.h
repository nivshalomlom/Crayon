#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "./transform.h"
#include "./material.h"
#include "../common.h"

class Geometry
{
    public:
        Transform transform;
        Material material;

        Geometry(glm::vec3 position = glm::vec3(0), Material material = Material())
        {
            this->transform = Transform(position);
            this->material = material;
        }
};

#endif