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
};

#endif