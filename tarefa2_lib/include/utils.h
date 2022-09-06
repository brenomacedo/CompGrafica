#pragma once

template <typename T>
class SmartPtr {
    public:
        T* pointer = nullptr;

        SmartPtr (T* pointer);
        
        T& operator * ();
        T* operator -> ();

        // the destructor is necessary for free the pointer's
        // memory when the function scope ends
        ~SmartPtr ();
};

template <typename T>
using Sp = SmartPtr<T>;