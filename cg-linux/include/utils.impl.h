#pragma once

#include <iostream>
#include <string>
#include "./utils.h"

template <typename T>
SmartPtr<T>::SmartPtr (T* pointer) {
    this->pointer = pointer;
}

template <typename T>
SmartPtr<T>::~SmartPtr () {
    // free memory when smart pointer is destructed
    delete this->pointer;
}

template <typename T>
T& SmartPtr<T>::operator* () {
    return *this->pointer;
}

template <typename T>
T* SmartPtr<T>::operator-> () {
    return this->pointer;
}

template <typename T>
SmartPtr<T> SmartPtr<T>::operator = (SmartPtr<T>& ptr) {
    delete this->pointer;
    this->pointer = ptr.pointer;
    ptr.pointer = nullptr;

    return *this;
}