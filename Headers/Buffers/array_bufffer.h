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

    public:
        ArrayBuffer(T* items = {}, int count = 0, size_t itemSize = 0) : StorageBuffer(items, count * itemSize)
        {
            this->array = Array<T>(items, count);
            this->itemSize = itemSize;
        }

        void Set(T* item, int index)
        {
            this->array[index] = item;
            this->UpdateData(this->array.items + index, this->itemSize, index * this->itemSize);
        }

        void SetRange(T* items, int length, int startIndex)
        {
            for (int i = 0; i < length; i++)
                this->array[startIndex + i] = items[i];

            this->UpdateData(this->array.items + startIndex, length * this->itemSize, startIndex * this->itemSize);
        }

        T Get(int index) { return this->array[index]; }

        void Dispose()
        {
            StorageBuffer::Dispose();
            this->array.Dispose();
        }
};

#endif