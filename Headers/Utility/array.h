#ifndef _ARRAY_H
#define _ARRAY_H

#include "./disposable.h"
#include "./enumerable.h"

template <typename T>

class Array : public Enumerable<T>
{
    private:
        int length;

    public:
        T* items;
        
        Array(T* items, int length)
        {
            this->items = items;
            this->length = length;
        }

        Array(int length)
        {
            this->items = new T[length];
            this->length = length;
        }

        Array() : Array(nullptr, 0) {}

        void Dispose() { delete [] this->items; }

        int Count() const { return this->length; }

        T & operator [](int i) { return this->items[i]; }
        
        T operator [](int i) const { return this->items[i]; }
};

#endif