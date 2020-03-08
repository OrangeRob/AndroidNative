#include <base.h>
#include <cstring>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nativejni_jni_JNIReferenceType_callNativeStringArray(JNIEnv *env, jobject thiz,
                                                              jobjectArray str_array) {
    int len = env->GetArrayLength(str_array);
    jstring strings[len];
//    const char *pCharArr[len];

    for(int i = 0; i < len; i++)
        strings[i] = static_cast<jstring>(env->GetObjectArrayElement(str_array, i));

//    for(int i = 0; i < len; i++)
//        pCharArr[i] = env->GetStringUTFChars(strings[i], 0);
//
//    for(int i = 0; i < len; i++)
//        env->ReleaseStringUTFChars(strings[i], pCharArr[i]);

    return strings[0];
}