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
        
        void Dispose() { glDeleteProgram(this->progID);}
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
    public:
        PostProcesingProgram(std::string fragmentShaderPath) 
            : ShaderProgram(fragmentShaderPath, "./Shaders/Vertex/fullscreen.vert") {}

        void Draw() { glDrawArrays(GL_TRIANGLES, 0, 3); }

        virtual void BindTextures(Texture2D source, Texture2D target) = 0;
};

#endif