#ifndef _BLOOM_H
#define _BLOOM_H

#include "../Graphics/program.h"

class BloomProgram : public PostProcesingProgram
{
    private:
        GLuint textureSizeLocation;
        GLuint textureLocation;

    public:
        BloomProgram(float bloomThreshold, float bloomIntensity) : PostProcesingProgram("./Shaders/Fragment/bloom.frag")
        {
            this->textureSizeLocation = glGetUniformLocation(this->Id(), "textureSize");
            this->textureLocation = glGetUniformLocation(this->Id(), "textureSampler");

            glUniform1f(glGetUniformLocation(this->Id(), "bloomThreshold"), bloomThreshold);
            glUniform1f(glGetUniformLocation(this->Id(), "bloomIntensity"), bloomIntensity);
        }

        void LoadSourceTexture(const Texture2D source)
        {
            this->Mount();
            source.Bind();

            glActiveTexture(GL_TEXTURE0);
            glUniform1i(this->textureLocation, 0);

            const glm::vec2 size = source.Size();
            glUniform2f(this->textureSizeLocation, size.x, size.y);
        }
};

#endif