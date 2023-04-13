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
        ArrayBuffer(T* items, int count) : StorageBuffer(items, count * sizeof(T))
        {
            this->array = Array<T>(items, count);
        }

        void Set(T* item, int index)
        {
            this->array[index] = item;
            this->UpdateData(this->array.items + index, sizeof(T), index * sizeof(T));
        }

        void SetRange(T* items, int length, int startIndex)
        {
            for (int i = 0; i < length; i++)
                this->array[startIndex + i] = items[i];

            this->UpdateData(this->array.items + startIndex, length * sizeof(T), startIndex * sizeof(T));
        }

        T Get(int index) { return this->array[index]; }
};

#endif