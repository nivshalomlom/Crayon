#ifndef _LIST_H
#define _LIST_H

#include "./disposable.h"
#include "./enumerable.h"

template <typename T>

class List : public Enumerable<T>
{
    private:
        int capacity;
        int count;
        T* array;

        void ResizeTo(int capacity)
        {
            int min = capacity < this->capacity ? capacity : this->capacity;
            T* temp = new T[capacity];

            for (int i = 0; i < min; i++)
                temp[i] = this->array[i];

            delete [] this->array;
            this->array = temp;
            this->capacity = capacity;
        }

    public:
        List(int capacity = 10)
        {
            this->capacity = capacity;
            this->count = 0;
            this->array = new T[capacity];
        }

        void Add(T item)
        {
            if (this->count >= this->capacity)
                this->ResizeTo(2 * this->capacity);

            this->array[this->count++] = item;
        }

        int IndexOf(T item, int (*comparator)(T, T))
        {
            for (int i = 0; i < this->count; i++)
                if (comparator(item, this->array[i]) == 0)
                    return i;

            return -1;
        }

        T* ToArray()
        {
            T* array = new T[this->count];
            for (int i = 0; i < this->count; i++)
                array[i] = this->array[i];

            return array;
        }
        
        void Dispose() { delete [] this->array; }

        int Count() const { return this->count; }

        T operator [](int index) const { return array[index]; }
        
        T & operator [](int index) { return array[index]; }
};

#endif