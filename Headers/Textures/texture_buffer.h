#ifndef _TEXRENDERER_H
#define _TEXRENDERER_H

#include "../PostProccessing/texture_copy.h"
#include "../Utility/array.h"
#include "../Utility/list.h"

class TextureBuffer : public Disposable
{
    private:
        List<PostProcesingProgram*> postProcesing;

    protected:
        GLuint frameBuffer;

        virtual void RenderTexture(Texture2D texture, glm::ivec2 min, glm::ivec2 max) = 0;

    public:
        TextureBuffer()
        {
            this->postProcesing = List<PostProcesingProgram*>();
            glGenFramebuffers(1, &this->frameBuffer);
        }

        void RenderToBuffer(Texture2D texture, glm::ivec2 min, glm::ivec2 max)
        {
            if (this->postProcesing.Count() == 0)
                this->RenderTexture(texture, min, max);
            else
            {
                Array<Texture2D> textures = Array<Texture2D>(this->postProcesing.Count());
                glm::vec2 textureSize = texture.Size();

                for (int i = 0; i < textures.Count(); i++)
                {
                    PostProcesingProgram* program = this->postProcesing[i];
                    Texture2D source = i > 0 ? textures[i - 1] : texture;

                    program->Mount();
                    program->LoadTextures(source, textures[i] = Texture2D(textureSize.x, textureSize.y, texture.RenderFormat()));
                    program->Draw();
                }

                this->RenderTexture(textures[textures.Count() - 1], min, max);
                Enumerable<PostProcesingProgram*>::DisposeEnumerable(&textures);
            }
        }

        virtual void Dispose() 
        { 
            glDeleteFramebuffers(1, &this->frameBuffer); 
            Enumerable<PostProcesingProgram*>::DisposeEnumerable(&this->postProcesing);
        }

        void AddPostProcessing(PostProcesingProgram* program) { this->postProcesing.Add(program); }
};

class TextureBlitBuffer : public TextureBuffer
{
    protected:
        void RenderTexture(Texture2D texture, glm::ivec2 min, glm::ivec2 max)
        {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBuffer);
            glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.Id(), 0);

            glm::ivec2 texSize = texture.Size();
            glBlitFramebuffer(0, 0, texSize.x, texSize.y, min.x, min.y, max.x, max.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        }

    public:
        TextureBlitBuffer() : TextureBuffer() {}
};

class TextureCopyBuffer : public TextureBuffer
{
    private:
        TextureCopyProgram* copyProgram;
        Texture2D* output;

    protected:
        void RenderTexture(Texture2D texture, glm::ivec2 min, glm::ivec2 max)
        {
            if (this->output != nullptr)
                this->output->Dispose();

            glm::vec2 textureSize = texture.Size();
            *output = Texture2D(
                textureSize.x, 
                textureSize.y, 
                texture.RenderFormat()
            );

            this->copyProgram->Mount();
            this->copyProgram->LoadTextures(texture, *this->output);
            this->copyProgram->Draw();
        }
    
    public:
        TextureCopyBuffer() : TextureBuffer() 
        {
            this->copyProgram = new TextureCopyProgram();
            this->output = nullptr;
        }

        void Dispose()
        {
            this->copyProgram->Dispose();
            delete this->copyProgram;

            if (this->output != nullptr)
            {
                this->output->Dispose();
                delete this->output;
            }

            TextureBuffer::Dispose();
        }

        const Texture2D* OutputTexture() { return this->output; }
};

#endif