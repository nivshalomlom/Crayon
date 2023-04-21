#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "../common.h"

struct Material
{
    public:
        glm::vec4 emissionColor;
        glm::vec4 baseColor;
        
        float emissionStrength;
        float reflectance;
        float roughness;
        float metallic;
        
        Material(glm::vec3 baseColor = glm::vec3(0), glm::vec3 emissionColor = glm::vec3(0), float emissionStrength = 0, float metallic = 0, float roughness = 0, float reflectance = 0)
        {
            this->emissionColor = glm::vec4(emissionColor, 1.0f);
            this->baseColor = glm::vec4(baseColor, 1.0f);
            this->emissionStrength = emissionStrength;
            this->reflectance = reflectance;
            this->roughness = roughness;
            this->metallic = metallic;
        }
};

#endif