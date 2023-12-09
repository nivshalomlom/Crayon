#ifndef _STORAGE_BUFFER_H
#define _STORAGE_BUFFER_H

#include "../Utility/disposable.h"
#include "../common.h"

class StorageBuffer : public Disposable
{
    private:
        GLuint storageBuffer;

        static void InitializeBuffer(GLuint* storageBuffer, void* data, size_t size)
        {
            glGenBuffers(1, storageBuffer);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, *storageBuffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }

    public:
        StorageBuffer(void* data, size_t size)
        {
            InitializeBuffer(&this->storageBuffer, data, size);
        }

        StorageBuffer(size_t numBytes)
        {
            char* bytes = new char[numBytes];
            
            InitializeBuffer(&this->storageBuffer, bytes, numBytes * sizeof(char));

            delete [] bytes;
        }

        void UpdateData(void* data, size_t size, size_t offset)
        {
            this->Bind();
            
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
            
            this->Unbind();
        }

        void BindToStorageBlock(GLuint binding) const
        {
            this->Bind();
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, this->storageBuffer);
            this->Unbind();
        }

        void Bind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->storageBuffer); }

        void Unbind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }

        virtual void Dispose() { glDeleteBuffers(1, &this->storageBuffer); }
};

#endif