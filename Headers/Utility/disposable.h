#ifndef _DISPOSABLE_H
#define _DISPOSABLE_H

class Disposable
{
    public:
        virtual void Dispose() = 0;

        static void DisposePointer(Disposable* value)
        {
            value->Dispose();
            delete value;
        }
};

#endif