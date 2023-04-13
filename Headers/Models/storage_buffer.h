#ifndef _STORAGE_BUFFER_H
#define _STORAGE_BUFFER_H

#include "../common.h"

class StorageBuffer
{
    private:
        GLuint storageBuffer;
        size_t size;

    public:
        StorageBuffer(void* data, size_t size)
        {
            glGenBuffers(1, &this->storageBuffer);
            this->size = size;

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->storageBuffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }

        void UpdateData(void* data, size_t size, size_t offset)
        {
            this->Bind();
            
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
            
            this->Unbind();
        }

        void BindToStorageBlock(GLuint program, GLuint binding, const char* blockName)
        {
            this->Bind();
            
            glBindBufferRange(GL_SHADER_STORAGE_BUFFER, binding, this->storageBuffer, 0, this->size);
            glShaderStorageBlockBinding(
                program,
                glGetProgramResourceIndex(program, GL_SHADER_STORAGE_BLOCK, blockName), 
                binding
            );

            this->Unbind();
        }

        void Bind() { glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->storageBuffer); }

        void Unbind() { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }
};

#endif