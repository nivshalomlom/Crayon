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
        size_t itemSize;

        char* buildBuffer(T* items, int length, size_t itemSize)
        {
            char* buffer = new char[sizeof(int) + length * itemSize];
            this->array = Array<T>(items, length);

            memcpy(buffer, &this->array.length, sizeof(int));
            memcpy(buffer + sizeof(int), items, length * itemSize);

            return buffer;
        }

    public:
        ArrayBuffer(T* items, int length, size_t itemSize, int binding) 
            : StorageBuffer(this->buildBuffer(items, length, itemSize), sizeof(int) + length * itemSize, binding)
        {
            this->itemSize = itemSize;
        }

        void Set(T item, int index)
        {
            this->array[index] = item;

            this->UpdateData(
                &this->array[index], 
                this->itemSize, 
                sizeof(int) + index * this->itemSize
            );
        }

        void SetRange(T* items, int length, int startIndex)
        {
            for (int i = 0; i < length; i++)
            {
                int index = startIndex + i;
                this->array[index] = items[i];
            }

            this->UpdateData(
                &this->array[startIndex], 
                this->itemSize * length,
                sizeof(int) + startIndex * this->itemSize
            );
        }

        T Get(int index) { return this->array[index]; }
};

#endif