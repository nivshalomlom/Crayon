#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../Utility/disposable.h"
#include "./texture_file.h"
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

    public:
        Texture2D(int width = 0, int height = 0, GLenum renderFormat = GL_RGBA32F)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &this->texture);
            this->renderFormat = renderFormat;
            this->size = glm::ivec2(width, height);

            SetTextureParameters(this->texture);
            glTextureStorage2D(this->texture, 1, renderFormat, width, height);
        }

        Texture2D(TextureFile* file, GLenum renderFormat = GL_RGBA32F)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &this->texture);
            this->renderFormat = renderFormat;
            this->size = file->Dimensions();

            this->Bind();
            SetTextureParameters(this->texture);
            glTexImage2D(GL_TEXTURE_2D, 0, renderFormat, size.x, size.x, 0, file->Format(), GL_UNSIGNED_BYTE, file->ReadBytes());
        }

        void BindToImage(GLuint unit, GLenum access = GL_READ_ONLY) const
        {
            glBindImageTexture(unit, this->texture, 0, GL_FALSE, 0, access, this->renderFormat);
        }

        GLenum RenderFormat() const { return this->renderFormat; }

        GLuint Id() const { return this->texture; }

        glm::vec2 Size() const { return this->size; }

        void Bind() const { glBindTexture(GL_TEXTURE_2D, this->texture); }

        void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

        void Dispose() { glDeleteTextures(1, &this->texture); }
};

#endif