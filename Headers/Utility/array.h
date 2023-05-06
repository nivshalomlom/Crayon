#ifndef _ARRAY_H
#define _ARRAY_H

#include "./disposable.h"

template <typename T>

class Array : public Disposable
{
    public:
        int length;
        T* items;

        Array(T* items, int length)
        {
            this->items = items;
            this->length = length;
        }

        Array() : Array(nullptr, 0) {}

        int Length() { return this->length; }

        T operator [](int i) const { return this->items[i]; }
        
        T & operator [](int i) { return this->items[i]; }

        void Dispose() { delete [] this->items; }
};

#endif