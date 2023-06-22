#ifndef _TONE_MAPPING_H
#define _TONE_MAPPING_H

#include "../Graphics/program.h"

class ToneMappingProgram : public PostProcesingProgram
{
    private:
        GLuint textureLocation;

    public:
        ToneMappingProgram(float exposure = 1.0, float gamma = 2.2) : PostProcesingProgram("./Shaders/Fragment/tone.frag")
        {
            this->Mount();
            this->textureLocation = glGetUniformLocation(this->Id(), "textureSampler");
            
            glUniform1f(glGetUniformLocation(this->Id(), "exposure"), exposure);
            glUniform1f(glGetUniformLocation(this->Id(), "gamma"), gamma);
        }

        void LoadSourceTexture(const Texture2D source, int currentPass)
        {
            this->Mount();
            source.Bind();

            glActiveTexture(GL_TEXTURE0);
            glUniform1i(this->textureLocation, 0);
        }
};

#endif