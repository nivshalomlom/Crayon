#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "../common.h"

struct Material
{
    public:
        glm::vec4 emissionColor;
        glm::vec4 baseColor;
        
        int reflectance;
        int roughness;
        int metallic;
        
        Material(glm::vec3 baseColor = glm::vec3(0), glm::vec3 emissionColor = glm::vec3(0), int metallic = 0, int roughness = 0, int reflectance = 0)
        {
            this->emissionColor = glm::vec4(emissionColor, 1.0f);
            this->baseColor = glm::vec4(baseColor, 1.0f);
            this->reflectance = reflectance;
            this->roughness = roughness;
            this->metallic = metallic;
        }

    private:
        // This is only here to make the material size divisable by 4 to work with std430 rules
        int padding = 0;
};

#endif