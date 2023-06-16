#ifndef _TEXRENDERER_H
#define _TEXRENDERER_H

#include "../Utility/disposable.h"
#include "../Utility/list.h"
#include "../Utility/array.h"
#include "../Graphics/program.h"
#include "./texture.h"
#include "../common.h"

class TextureRenderer : public Disposable
{
    private:
        List<PostProcesingProgram*> postProcesing;
        GLuint frameBuffer;

        void BlitTextureToScreen(Texture2D texture, glm::ivec2 min, glm::ivec2 max)
        {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBuffer);
            glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.Id(), 0);

            glm::ivec2 texSize = texture.Size();
            glBlitFramebuffer(0, 0, texSize.x, texSize.y, min.x, min.y, max.x, max.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        }

    public:
        TextureRenderer()
        {
            this->postProcesing = List<PostProcesingProgram*>();
            glGenFramebuffers(1, &this->frameBuffer);
        }

        void RenderToScreen(Texture2D texture, glm::ivec2 min, glm::ivec2 max)
        {
            if (this->postProcesing.Count() == 0)
                this->BlitTextureToScreen(texture, min, max);
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

                this->BlitTextureToScreen(textures[textures.Count() - 1], min, max);
                Enumerable<PostProcesingProgram*>::DisposeEnumerable(&textures);
            }
        }

        void Dispose() 
        { 
            glDeleteFramebuffers(1, &this->frameBuffer); 
            Enumerable<PostProcesingProgram*>::DisposeEnumerable(&this->postProcesing);
        }

        void AddPostProcessing(PostProcesingProgram* program) { this->postProcesing.Add(program); }
};

#endif