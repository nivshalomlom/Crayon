#ifndef _ARRAY_BUFFER_H
#define _ARRAY_BUFFER_H

#include "../Utility/array.h"
#include "./storage_buffer.h"

template <typename T>

class ArrayBuffer : public StorageBuffer
{
    private:
        using StorageBuffer::UpdateData;

        Array<T> array;

    public:
        ArrayBuffer(T* items, int count) : StorageBuffer(nullptr, sizeof(int) + count * sizeof(T))
        {
            this->array = Array<T>(items, count);
            this->Bind();

            void* bufferPtr = glMapBufferRange(
                GL_SHADER_STORAGE_BUFFER, 
                0, sizeof(int) + count * sizeof(T), 
                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
            );

            int* lengthPtr = (int*) bufferPtr;
            T* itemsPtr = (T*)((char*) bufferPtr + sizeof(int));

            memcpy(lengthPtr, &this->array.length, sizeof(int));
            memcpy(itemsPtr, this->array.items, count * sizeof(T));
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

            this->Unbind();
        }
};

#endif