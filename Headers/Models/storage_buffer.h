#ifndef _STORAGE_BUFFER_H
#define _STORAGE_BUFFER_H

#include "../common.h"

class StorageBuffer
{
    private:
        GLuint storageBuffer;
        GLuint binding;

    public:
        StorageBuffer(void* data, size_t size, GLuint binding)
        {
            glGenBuffers(1, &this->storageBuffer);
            this->binding = binding;

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->storageBuffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, this->storageBuffer);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }

        void UpdateData(void* data, size_t size, size_t offset)
        {
            this->Bind();
            
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
            
            this->Unbind();
        }

        void BindToStorageBlock(GLuint program, const char* blockName)
        {
            this->Bind();
            
            glShaderStorageBlockBinding(
                program, 
                glGetProgramResourceIndex(program, GL_SHADER_STORAGE_BLOCK, blockName), 
                this->binding
            );

            this->Unbind();
        }

        void Bind() { glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->storageBuffer); }

        void Unbind() { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }
};

#endif