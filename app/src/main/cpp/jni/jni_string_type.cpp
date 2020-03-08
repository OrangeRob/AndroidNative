#include <base.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nativejni_jni_JNIString_callNativeString(JNIEnv *env, jobject thiz, jstring str) {
    jboolean isCopy = JNI_FALSE;
    const char* s = env->GetStringUTFChars(str, &isCopy);
    LOGD(">> java string is : %s", s);
    env->ReleaseStringUTFChars(str, s);

    return env->NewStringUTF("this is C style string");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIString_stringMethod(JNIEnv *env, jobject thiz, jstring str) {
    char buf[128] = {0};
    int len = env->GetStringLength(str);
    LOGD(">> java string len = %d", len);

    env->GetStringUTFRegion(str, 0, len - 4, buf);
    LOGD(">> set java string region: %s", buf);
}
