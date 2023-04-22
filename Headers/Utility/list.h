#ifndef _LIST_H
#define _LIST_H

template <typename T>

class List
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

        T Get(int index) const { return this->array[index]; }

        int Count() const { return this->count; }
};

#endif