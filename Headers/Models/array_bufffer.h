#ifndef _ARRAY_BUFFER_H
#define _ARRAY_BUFFER_H

#include "../Utility/array.h"
#include "./storage_buffer.h"

template <typename T>

class ArrayBuffer : public StorageBuffer
{
    private:
        Array<T>* data;
        size_t itemSize;

        void Update(int startIndex, int count) 
        { 
            this->UpdateData(
                (void*) &this->data,
                this->itemSize * count, 
                this->itemSize * startIndex
            );
        }

        Array<T>* InitializeData(T* items, int length)
        {
            this->data = new Array<T>(items, length);
            return this->data;
        }

    public:
        ArrayBuffer(T* items, size_t itemSize, int length) : StorageBuffer((void*) InitializeData(items, length), length * itemSize + sizeof(int))
        {
            this->itemSize = itemSize;
        }

        void Set(int index, T item)
        {
            Array<T> array = *this->data;
            array[index] = item;
            this->Update(index, 1);
        }

        void SetRange(int startIndex, T* items, int count)
        {
            Array<T> array = *this->data;
            for (int i = 0; i < count; i++)
            {
                int index = startIndex + i;
                array[index] = items[index];
            }

            this->Update(startIndex, count);
        }

        T Get(int index) 
        { 
            Array<T> array = *this->data;
            return array[index]; 
        }
};

#endif