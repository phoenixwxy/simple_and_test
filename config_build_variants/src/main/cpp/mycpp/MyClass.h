//
// Created by mi on 6/19/24.
//

#ifndef SIMPLE_TEST_CONFIG_BUILD_VARIANTS_SRC_MAIN_CPP_MYCPP_MYCLASS_H_
#define SIMPLE_TEST_CONFIG_BUILD_VARIANTS_SRC_MAIN_CPP_MYCPP_MYCLASS_H_

class MyClass {
public:
    MyClass();
    ~MyClass();
    void myMethod();
    int myValue;
};

#ifdef __cplusplus
extern "C"{
#endif

void* createMyClass();
void destroyMyClass(void* instance);
void callMyMethod(void* instance);
int getMyValue(void* instance);

#ifdef __cplusplus
}
#endif

#endif //SIMPLE_TEST_CONFIG_BUILD_VARIANTS_SRC_MAIN_CPP_MYCPP_MYCLASS_H_
