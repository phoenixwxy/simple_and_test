//
// Created by phoenix on 2024/3/18.
//
#define LOG_TAG "JNI_Static"
#include <jni.h>

#include <android/log.h>

#define LOG(prio, ...) __android_log_print(prio, LOG_TAG, __VA_ARGS__)

#define LOGV(...) LOG(ANDROID_LOG_VERBOSE, __VA_ARGS__)
#define LOGD(...) LOG(ANDROID_LOG_DEBUG, __VA_ARGS__)
#define LOGI(...) LOG(ANDROID_LOG_INFO, __VA_ARGS__)
#define LOGE(...) LOG(ANDROID_LOG_ERROR, __VA_ARGS__)


static void helloJNI(JNIEnv *env, jobject thiz) {
    LOGI("Hello Shared JNI");
}

static const JNINativeMethod gMethods[] = {
        {"helloJNI", "()V", (void *) helloJNI}
};

static int
jniRegisterNativeMethods(JNIEnv *env, const char *className, const JNINativeMethod *gMethods,
                         int numMethods) {
    jclass clazz;

    clazz = env->FindClass(className);
    if (clazz == nullptr) {
        LOGE("failed find the class name: %s", className);
        return -1;
    }

    int result = 0;
    if(env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        LOGE("Register registration unable to find the class name: %s", className);
        return result;
    }

    env->DeleteLocalRef(clazz);
    return result;
}

static const char* gClassName = "com/example/jni_learn/jni/JNIKotlinShared";

jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env = nullptr;
    jint result = -1;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    jint size = sizeof(gMethods) / sizeof(JNINativeMethod);
    jniRegisterNativeMethods(env, gClassName, gMethods, size);

    return JNI_VERSION_1_6;
}
