#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../Utility/disposable.h"
#include "../common.h"

class Texture2D : public Disposable
{
    private:
        GLenum renderFormat;
        GLuint texture;
        glm::ivec2 size;

        static void SetTextureParameters(GLuint texture)
        {
            glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        void InitiallizeTexture(int width, int height, GLenum renderFormat)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &this->texture);
            this->renderFormat = renderFormat;
            this->size = glm::ivec2(width, height);

            SetTextureParameters(this->texture);
            glTextureStorage2D(this->texture, 1, renderFormat, width, height);
        }

    public:
        Texture2D(int width = 0, int height = 0, GLenum renderFormat = GL_RGBA32F)
        {
            InitiallizeTexture(width, height, renderFormat);
        }

        void BindToImage(GLuint unit, GLenum access = GL_READ_ONLY)
        {
            glBindImageTexture(unit, this->texture, 0, GL_FALSE, 0, access, this->renderFormat);
        }

        void Resize(int width, int height)
        {
            glDeleteTextures(1, &this->texture);
            InitiallizeTexture(width, height, this->renderFormat);
        }

        GLuint Id() { return this->texture; }

        glm::vec2 Size() { return this->size; }

        void Bind() { glBindTexture(GL_TEXTURE_2D, this->texture); }

        void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

        void Dispose() { glDeleteTextures(1, &this->texture); }
};

#endif