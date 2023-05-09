#ifndef _OBJECT_BUFFER_H
#define _OBJECT_BUFFER_H

#include "./storage_buffer.h"

template <typename T>

class ObjectBuffer : public StorageBuffer
{
    private:
        T value;
        size_t size;

    public:
        ObjectBuffer(T data, size_t size) : StorageBuffer(&data, size)
        {
            this->value = data;
            this->size = size;
        }

        ObjectBuffer() : StorageBuffer(nullptr, 0)
        {
            this->value = T{};
            this->size = 0;
        }

        void SetValue(T data)
        {
            this->value = data;
            this->UpdateData(&this->value, this->size, 0);
        }

        const T GetValue() const { return this->value; }
};

#endif