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
        ArrayBuffer(Array<T> array, int binding) : StorageBuffer(nullptr, sizeof(int) + array.length * sizeof(T), binding), array(array)
        {
            UpdateData(&this->array.length, sizeof(int), 0);
            UpdateData(this->array.items, this->array.length * sizeof(T), sizeof(int));
        }

        void Set(T item, int index) 
        {
            this->array[index] = item;
            size_t itemSize = sizeof(T);

            this->UpdateData(
                &this->array[index],
                itemSize,
                index * itemSize
            );
        }

        T Get(int index) { return this->array[index]; }
};

#endif