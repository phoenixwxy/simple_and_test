#include <jni.h>

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("jni_learn");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("jni_learn")
//      }
//    }
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1learn_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("this string is from JNI");
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1learn_MainActivity_getJNICppString(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("TODO");
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1learn_MainActivity_getJNICppStaticString(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("TODO");
}

/**
 * \brief 这个函数获取从kotlin/java传下来的对象，并调用其方法后返回
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1learn_MainActivity_getJNIKotlinString(JNIEnv *env, jobject thiz,
                                                            jobject jni_kotlin) {
    jclass k_class = env->GetObjectClass(jni_kotlin);
    jmethodID k_getString = env->GetMethodID(k_class, "getStr", "()Ljava/lang/String;");
    jstring jni_string = (jstring) env->CallObjectMethod(jni_kotlin, k_getString);
    char *cpp_string = (char *) env->GetStringUTFChars(jni_string, 0);
    return env->NewStringUTF(cpp_string);
}

/**
 * \brief: 这个函数接受外部的kotlin/java对象，然后在jni中重新构造并且返回。
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jni_1learn_MainActivity_getJNIKotlinObj__Lcom_example_jni_1learn_jni_JNIKotlin_2(JNIEnv *env, jobject thiz,
                                                                                                  jobject jni_kotlin) {
    jclass k_class = env->FindClass("com/example/jni_learn/jni/JNIKotlin");

    jfieldID num = env->GetFieldID(k_class, "num", "I");
    jfieldID str = env->GetFieldID(k_class, "str", "Ljava/lang/String;");

    //属性赋值，person为传入的Java对象
    env->SetObjectField(jni_kotlin, str, env->NewStringUTF("nativeString"));
    env->SetIntField(jni_kotlin, num, 20);

    return jni_kotlin;
}

/**
 * \brief 不接受外部kotlin/java对象，直接构造对象并返回
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jni_1learn_MainActivity_getJNIKotlinObj__(JNIEnv *env, jobject thiz) {
    jclass k_class = env->FindClass("com/example/jni_learn/jni/JNIKotlin");

    jmethodID k_construct = env->GetMethodID(k_class, "<init>", "(ILjava/lang/String;)V");

    jstring str = env->NewStringUTF("nativeString_createByNative");
    jobject k_object = env->NewObject(k_class, k_construct, 10, str);

    return k_object;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1learn_MainActivity_getJNIKotlinStaticString(JNIEnv *env, jobject thiz,
                                                                  jobject jni_kotlin) {
    jclass k_class = env->GetObjectClass(jni_kotlin);
    jmethodID k_getString = env->GetMethodID(k_class, "staticGetStr", "()Ljava/lang/String;");
    jstring jni_string = (jstring) env->CallObjectMethod(jni_kotlin, k_getString);
    char *cpp_string = (char *) env->GetStringUTFChars(jni_string, 0);
    return env->NewStringUTF(cpp_string);
}