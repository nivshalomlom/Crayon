#ifndef _ENUMERABLE_H
#define _ENUMERABLE_H

#include "./disposable.h"

template <typename T>

class Enumerable : public Disposable
{
    public:
        virtual T operator [](int index) const = 0;
        
        virtual T & operator [](int index) = 0;

        virtual int Count() const = 0;

        template <typename U>

        static void DisposeEnumerable(Enumerable<U>* enumerable)
        {
            for (int i = 0; i < enumerable->Count(); i++)
                (*enumerable)[i].Dispose();

            enumerable->Dispose();
        }

        template <typename U>

        static void DisposeEnumerable(Enumerable<U*>* enumerable)
        {
            for (int i = 0; i < enumerable->Count(); i++)
                (*enumerable)[i]->Dispose();

            enumerable->Dispose();
        }
};

#endif