#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIAccessMethod_accessInstanceMethod(JNIEnv *env, jobject thiz,
        jobject animal) {
    jclass cls = env->GetObjectClass(animal);

    /* public void callInstanceMethod(int num) */
    jmethodID mid = env->GetMethodID(cls, "callInstanceMethod", "(I)V");
    env->CallVoidMethod(animal, mid, 777);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIAccessMethod_accessStaticMethod(JNIEnv *env, jobject thiz,
        jobject animal) {
    jclass cls = env->GetObjectClass(animal);

    /* 1. public static String callStaticMethod(String str) */
    jmethodID mid = env->GetStaticMethodID(cls, "callStaticMethod", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring str = env->NewStringUTF("jstring from jni.");
    jobject ret = env->CallStaticObjectMethod(cls, mid, str);
    const char *strReturn = env->GetStringUTFChars(static_cast<jstring>(ret), 0);
    LOGD("jni >> got return : %s", strReturn);
    env->ReleaseStringUTFChars(static_cast<jstring>(ret), strReturn);
    env->DeleteLocalRef(ret);

    /* 2. public static String callStaticMethod(String[] strs, int num) */
    mid = env->GetStaticMethodID(cls, "callStaticMethod", "([Ljava/lang/String;I)Ljava/lang/String;");
    jclass strClass = env->FindClass("java/lang/String");
    int size = 2;
    jobjectArray strArray = env->NewObjectArray(size, strClass, nullptr);
    for(int i = 0; i < size; i++) {
        jstring strItem = env->NewStringUTF("string in native");
        env->SetObjectArrayElement(strArray, i, strItem);
    }

    env->CallStaticObjectMethod(cls, mid, strArray, size);
}