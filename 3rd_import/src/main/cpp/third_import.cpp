#include <jni.h>

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("a3rd_import");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("a3rd_import")
//      }
//    }

#include "ImportSimple.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_example_a3rd_1import_MainActivity_testC2dDunc(JNIEnv *env, jobject thiz) {
    phoenix::ImportSimple import_simple;
}