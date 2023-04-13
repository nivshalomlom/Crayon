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
            this->UpdateData(&this->array.length, sizeof(int), 0);
            this->UpdateData(this->array.items, count * sizeof(T), sizeof(int));
        }
};

#endif