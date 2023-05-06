#ifndef _OBJECT_BUFFER_H
#define _OBJECT_BUFFER_H

#include "./storage_buffer.h"

template <typename T>

class ObjectBuffer : public StorageBuffer
{
    private:
        T data;
        size_t size;

    public:
        ObjectBuffer(T data, size_t size) : StorageBuffer(&data, size)
        {
            this->data = data;
            this->size = size;
        }

        ObjectBuffer() : StorageBuffer(nullptr, 0)
        {
            this->data = T{};
            this->size = 0;
        }

        void ModifyObject(std::function<T(T)> modification)
        {
            this->data = modification(this->data);
            this->UpdateData(&this->data, this->size, 0);
        }

        const T Data() const { return this->data; }
};

#endif