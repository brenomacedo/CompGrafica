#pragma once

#include <iostream>
#include <string>

template <typename T>
class SmartPtr {
    public:
        T* pointer = nullptr;

        SmartPtr (T* pointer);
        
        T& operator * ();
        T* operator -> ();

        SmartPtr<T> operator = (SmartPtr<T>& ptr);

        // the destructor is necessary for free the pointer's
        // memory when the function scope ends
        ~SmartPtr ();
};

template <typename T>
using Sp = SmartPtr<T>;