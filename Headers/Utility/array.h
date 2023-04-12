#ifndef _ARRAY_H
#define _ARRAY_H

template <typename T>

class Array
{
    public:
        T* items;
        int length;

        Array(T* items, int length)
        {
            this->items = items;
            this->length = length;
        }

        Array() : Array(nullptr, 0) {}

        int Length() { return this->length; }

        T operator [](int i) const { return this->items[i]; }
        
        T & operator [](int i) { return this->items[i]; }
};

#endif