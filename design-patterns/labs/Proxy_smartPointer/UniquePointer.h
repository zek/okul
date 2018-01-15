#pragma once

#include "MyClass.h"
#include <iostream>

using namespace std;

class UniquePointer {
public:
    MyClass *ptr;

    UniquePointer(MyClass *myClass1) {
        this->ptr = myClass1;
    }

    ~UniquePointer() {
        if(this->ptr){
            cout << "Destroying object " << this->ptr->m_name << endl;
        }
    }

    UniquePointer(UniquePointer& uniquePointer) {
        if (this != &uniquePointer) {
            this->ptr = uniquePointer.ptr;
            uniquePointer.ptr = nullptr;
        }
    }

    MyClass *operator->() {
        return ptr;
    }

    UniquePointer& operator=(UniquePointer& uniquePointer) {
        if (this != &uniquePointer) {
            this->ptr = uniquePointer.ptr;
            uniquePointer.ptr = nullptr;
        }
        return *this;
    }

    void operator=(MyClass *myClass1) {
        cout << "Destroying object " << this->ptr->m_name << endl;
        this->ptr = myClass1;
    }

    void print() {
        if (ptr != nullptr) {
            cout << "This is a pointer to " << ptr->m_name << endl;
        }else{
            cout << "This is object  does not point to anything" << endl;
        }
    }
};