#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "../common.h"

struct Material
{
    public:
        glm::vec3 emissionColor;
        glm::vec3 baseColor;
        
        int reflectance;
        int roughness;
        int metallic;

        Material(glm::vec3 baseColor = glm::vec3(0), glm::vec3 emissionColor = glm::vec3(0), int metallic = 0, int roughness = 0, int reflectance = 0)
        {
            this->emissionColor = emissionColor;
            this->baseColor = baseColor;
            this->reflectance = reflectance;
            this->roughness = roughness;
            this->metallic = metallic;
        }
};

#endif