#include <base.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nativejni_jni_JNIStringType_callNativeString(JNIEnv *env, jobject thiz, jstring str) {
    jboolean isCopy = JNI_FALSE;
    const char* s = env->GetStringUTFChars(str, &isCopy);
    LOGD(">> java string is : %s", s);
    env->ReleaseStringUTFChars(str, s);

    return env->NewStringUTF("this is C style string");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIStringType_stringMethod(JNIEnv *env, jobject thiz, jstring str) {
    char buf[128] = {0};
    int len = env->GetStringLength(str);
    LOGD(">> java string len = %d", len);

    env->GetStringUTFRegion(str, 0, len - 4, buf);
    LOGD(">> set java string region: %s", buf);
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_nativejni_jni_JNIStringType_callNativeStringArray(JNIEnv *env, jobject thiz,
                                                           jobjectArray str_array) {
    int len = env->GetArrayLength(str_array);
    jstring strings[len];
    const char *pCharArr[len];

    for(int i = 0; i < len; i++)
        strings[i] = static_cast<jstring>(env->GetObjectArrayElement(str_array, i));

    for(int i = 0; i < len; i++)
        pCharArr[i] = env->GetStringUTFChars(strings[i], 0);

    for(int i = 0; i < len; i++)
        env->ReleaseStringUTFChars(strings[i], pCharArr[i]);

    jclass strClass = env->FindClass("java/lang/String");
    jobjectArray retArray = env->NewObjectArray(len, strClass, env->NewStringUTF(""));
    for(int i = 0; i < len; i++)
        env->SetObjectArrayElement(retArray, i, env->NewStringUTF(pCharArr[len - i - 1]));

    return retArray;
}
