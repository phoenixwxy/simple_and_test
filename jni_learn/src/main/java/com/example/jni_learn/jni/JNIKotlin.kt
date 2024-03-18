package com.example.jni_learn.jni

class JNIKotlin(private var num: Int, private var str: String) {

    companion object {
        const val s_Str : String = "Kotlin static string"
    }

    fun staticGetStr(): String {
        return s_Str
    }

    fun setStr(str: String) {
        this.str = str
    }

    fun getStr(): String {
        return str
    }

    fun setNum(num: Int) {
        this.num = num
    }

    fun getNum(): Int {
        return num
    }

    override fun toString(): String {
        return "JNIKotlin: str: $str, mNum: $num"
    }
}