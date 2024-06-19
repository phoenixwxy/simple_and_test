//
// Created by mi on 6/19/24.
//

#include "MyClass.h"

MyClass::MyClass() {
    myValue = 0;
}

MyClass::~MyClass() {
    // Destructor
}

void MyClass::myMethod() {
    // Implementation of myMethod
    myValue++;
}

extern "C" {
void* createMyClass() {
    return new MyClass();
}

void destroyMyClass(void* instance) {
    delete static_cast<MyClass*>(instance);
}

void callMyMethod(void* instance) {
    static_cast<MyClass*>(instance)->myMethod();
}

int getMyValue(void* instance) {
    return static_cast<MyClass*>(instance)->myValue;
}
}
