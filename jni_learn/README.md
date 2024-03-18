# JNI

JNI分为动态和静态两种方式

## 静态绑定

### 相互调用

Kotlin对象
```Kotlin
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
```

### 从Native返回Java/Kotlin对象
```cpp
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
```

## 动态绑定

动态绑定就是实现几个关键函数，然后实现类似于c++动态库绑定

```c++
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
```

在kotlin中使用

```Kotlin
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
```