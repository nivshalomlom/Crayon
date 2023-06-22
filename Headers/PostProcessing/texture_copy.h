#ifndef _TEXTURE_COPY_H
#define _TEXTURE_COPY_H

#include "../Graphics/program.h"

class TextureCopyProgram : public PostProcesingProgram
{
    private:
        GLuint textureLocation;

    public:
        TextureCopyProgram() : PostProcesingProgram("./Shaders/Fragment/copy.frag")
        {
            this->textureLocation = glGetUniformLocation(this->Id(), "textureSampler");
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