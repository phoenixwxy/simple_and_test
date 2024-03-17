package com.example.demo_vcpkg

class NativeLib {

    /**
     * A native method that is implemented by the 'demo_vcpkg' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'demo_vcpkg' library on application startup.
        init {
            System.loadLibrary("demo_vcpkg")
        }
    }
}