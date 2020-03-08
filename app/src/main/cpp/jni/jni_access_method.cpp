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

    /* public static String callStaticMethod(String str) */
    jmethodID mid = env->GetStaticMethodID(cls, "callStaticMethod", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring str = env->NewStringUTF("jstring from jni.");
    env->CallStaticObjectMethod(cls, mid, str);

    /* public static String callStaticMethod(String[] strs, int num) */
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