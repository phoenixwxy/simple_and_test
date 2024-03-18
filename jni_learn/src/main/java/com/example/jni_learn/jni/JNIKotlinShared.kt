package com.example.jni_learn.jni

import android.util.Log

class JNIKotlinShared {

    companion object {
        val TAG : String = JNIKotlinShared.javaClass.simpleName
        init {
            System.loadLibrary("jni_learn_shared")
        }
    }

    private external fun helloJNI()

    fun hello() {
        Log.i(TAG, "hello: Enter")
        helloJNI()
    }

}