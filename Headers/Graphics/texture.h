#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../common.h"

class Texture2D
{
    private:
        GLenum renderFormat;
        GLuint texture;

        static void SetTextureParameters(GLuint texture)
        {
            glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

    public:
        Texture2D(int width, int height, GLenum renderFormat = GL_RGBA32F)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &this->texture);
            this->renderFormat = renderFormat;

            SetTextureParameters(this->texture);
            glTextureStorage2D(this->texture, 1, renderFormat, width, height);
        }

        void BindToImage(GLuint unit, GLenum access = GL_READ_ONLY)
        {
            glBindImageTexture(unit, this->texture, 0, GL_FALSE, 0, access, this->renderFormat);
        }
};

#endif