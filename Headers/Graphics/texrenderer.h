#ifndef _TEXRENDERER_H
#define _TEXRENDERER_H

#include "../Utility/disposable.h"
#include "../Models/texture.h"
#include "./window.h"
#include "./program.h"

class TextureRenderer : public Disposable
{
    private:
        GLuint frameBuffer;

    public:
        TextureRenderer()
        {
            glGenFramebuffers(1, &this->frameBuffer);
        }

        void RenderToScreen(Texture2D texture, glm::ivec2 min, glm::ivec2 max)
        {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBuffer);
            glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.Id(), 0);

            glm::ivec2 texSize = texture.Size();
            glBlitFramebuffer(0, 0, texSize.x, texSize.y, min.x, min.y, max.x, max.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        }

        void Dispose() { glDeleteFramebuffers(1, &this->frameBuffer); }
};

#endif