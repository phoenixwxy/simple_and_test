package com.example.jni_learn

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.jni_learn.jni.JNIKotlin
import com.example.jni_learn.jni.JNIKotlinShared
import com.example.jni_learn.ui.theme.Simple_testTheme
import kotlin.math.log

class MainActivity : ComponentActivity() {

    companion object {
        val TAG: String = MainActivity.javaClass.name

        init {
            System.loadLibrary("jni_learn")
        }
    }

    // native functions

    private external fun stringFromJNI(): String

    private external fun getJNICppString(): String

    private external fun getJNICppStaticString(): String

    private external fun getJNIKotlinString(jniKotlin: JNIKotlin): String

    private external fun getJNIKotlinStaticString(jniKotlin: JNIKotlin) : String

    private external fun getJNIKotlinObj(jniKotlin: JNIKotlin): JNIKotlin

    private external fun getJNIKotlinObj(): JNIKotlin

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.i(TAG, "onCreate: 1111111")

        val jniKotlinShared = JNIKotlinShared()
        Log.i(TAG, "onCreate: Enter Hello")
        jniKotlinShared.hello()

        val strGetObjByKotlin = getJNIKotlinObj(jniKotlin = JNIKotlin(9, "kotlinString")).getStr()
        val strGetObj = getJNIKotlinObj().getStr()

        val strGetStringByObj = getJNIKotlinString(jniKotlin = JNIKotlin(15, "Kotlin String"))
        val strGetStaticString = getJNIKotlinStaticString(jniKotlin = JNIKotlin(10, "Kotlin Static String Get"))

        setContent {
            Simple_testTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Greeting(
                        "${stringFromJNI()}\n" +
                                "strGetObjByKotlin: $strGetObjByKotlin\n" +
                                "strGetObj: $strGetObj\n" +
                                "strGetStringByObj: $strGetStringByObj\n" +
                                "strGetStaticString: $strGetStaticString"
                    )
                }
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = name,
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    Simple_testTheme {
        Greeting("Android")
    }
}