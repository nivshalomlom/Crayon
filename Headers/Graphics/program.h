#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "../Utility/disposable.h"
#include "../Textures/texture.h"
#include "../common.h"

class Program : public Disposable
{
    protected:
        GLuint progID;

        void LinkShader() const
        {
            glLinkProgram(this->progID);
            glValidateProgram(this->progID);
        }

        Program() { this->progID = glCreateProgram(); };

        void AttachShader(GLuint* shader, std::string filePath, GLenum shaderType) const;

    public:

        GLuint Id() const { return this->progID; }

        void Mount() const { glUseProgram(this->progID); }
        
        virtual void Dispose() { glDeleteProgram(this->progID);}
};

class ShaderProgram : public Program
{
    public:
        ShaderProgram(std::string fragmentShaderPath, std::string vertexShaderPath) : Program()
        {
            GLuint frag = 0, vert = 0;
            this->AttachShader(&frag, fragmentShaderPath, GL_FRAGMENT_SHADER);
            this->AttachShader(&vert, vertexShaderPath, GL_VERTEX_SHADER);

            this->LinkShader();
            glDeleteShader(frag);
            glDeleteShader(vert);
        }

        ShaderProgram() : Program() {}

        virtual void Draw() = 0;
};

class ComputeProgram : public Program
{
    public:
        ComputeProgram(std::string computeShaderPath) : Program() 
        {
            GLuint compute = 0;
            this->AttachShader(&compute, computeShaderPath, GL_COMPUTE_SHADER); 

            this->LinkShader();
            glDeleteShader(compute);
        }

        ComputeProgram() : Program() {}

        void Dispatch(glm::ivec3 groups, GLuint barrierMask = GL_ALL_BARRIER_BITS) const 
        { 
            glDispatchCompute(groups.x, groups.y, groups.z);
            glMemoryBarrier(barrierMask);
        }
};

class PostProcesingProgram : public ShaderProgram
{
    private:
        const GLenum DRAW_BUFFERS[1] = {GL_COLOR_ATTACHMENT0};

        GLuint frameBuffer;

    public:
        PostProcesingProgram(std::string fragmentShaderPath) : ShaderProgram(fragmentShaderPath, "./Shaders/Vertex/fullscreen.vert") 
        {
            glGenFramebuffers(1, &this->frameBuffer);
        }

        void Draw() 
        { 
            glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
            glDrawArrays(GL_TRIANGLES, 0, 3); 
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void LoadTextures(Texture2D source, Texture2D target)
        {
            this->Mount();
            this->LoadSourceTexture(source);

            glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target.Id(), 0);
            glDrawBuffers(1, DRAW_BUFFERS);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Dispose()
        {
            Program::Dispose(); 
            glDeleteFramebuffers(1, &this->frameBuffer);
        }

        virtual void LoadSourceTexture(const Texture2D source) = 0;
};

#endif