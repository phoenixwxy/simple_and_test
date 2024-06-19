#include <jni.h>

#include <android/log.h>

#include <string>
#include <functional>

#include <dlfcn.h>


#define LOG_TAG "config_build_variants" // Replace with your actual application name
#define DEBUG
#ifdef DEBUG
#define logv(fmt, ...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, fmt, ##__VA_ARGS__)
#define logd(fmt, ...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##__VA_ARGS__)
#define logi(fmt, ...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##__VA_ARGS__)
#define logw(fmt, ...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, fmt, ##__VA_ARGS__)
#define loge(fmt, ...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##__VA_ARGS__)
#define logf(fmt, ...)  __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, fmt, ##__VA_ARGS__)
#else
#define logv(...) (void(0))  // No-op for verbose in release mode
#define logd(...) (void(0))  // No-op for debug in release mode
#define logi(...) (void(0))  // No-op for info in release mode
#define logw(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, fmt, ##__VA_ARGS__) // Keep warnings in release mode
#define loge(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##__VA_ARGS__) // Keep errors in release mode
#define logf(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, fmt, ##__VA_ARGS__) // Keep fatals in release mode
#endif


/**
 * the symbols in the libraries

class MyClass;

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
 */

void testLoadLibs(std::string libName) {

    std::function<void*()> createMyClass = nullptr;
    std::function<void(void*)> destroyMyClass = nullptr;
    std::function<void(void*)> callMyMethod = nullptr;
    std::function<int(void*)> getMyValue = nullptr;

    void* myClass = nullptr;
    int value = 0;

    void* handle = dlopen(libName.c_str(), RTLD_LAZY);
    if (!handle) {
        loge("PhoenixDebug failed dlopen %s", libName.c_str());
        goto close_handle;
    }

    // Get function pointers
    createMyClass = reinterpret_cast<void*(*)()>(dlsym(handle, "createMyClass"));
    if (!createMyClass) {
        loge("PhoenixDebug failed dlsym createMyClass");
        goto close_handle;
    }

    destroyMyClass = reinterpret_cast<void(*)(void*)>(dlsym(handle, "destroyMyClass"));
    if (!destroyMyClass) {
        loge("PhoenixDebug failed dlsym destroyMyClass");
        goto close_handle;
    }

    callMyMethod = reinterpret_cast<void(*)(void*)>(dlsym(handle, "callMyMethod"));
    if (!callMyMethod) {
        loge("PhoenixDebug failed dlsym callMyMethod");
        goto close_handle;
    }

    getMyValue = reinterpret_cast<int(*)(void*)>(dlsym(handle, "getMyValue"));
    if (!getMyValue) {
        loge("PhoenixDebug failed dlsym getMyValue");
        goto close_handle;
    }

    myClass = createMyClass(); // Call the function from the loaded library
    callMyMethod(myClass);
    value = getMyValue(myClass);

    loge("PhoenixDebug value is %d", value);

    destroyMyClass(myClass);

close_handle:
    dlclose(handle); // Close the library when done
}

extern "C"
JNIEXPORT void JNICALL
Java_com_phoenix_config_1build_1variants_MainActivity_test_1load_1libraries(JNIEnv *env,
                                                                            jobject thiz) {
    testLoadLibs("libmycpp.root.so");
    testLoadLibs("libmycpp.jniLibs.so");
    testLoadLibs("libmycpp.libs.so");
}