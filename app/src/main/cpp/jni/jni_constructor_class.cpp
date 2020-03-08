#include <base.h>

extern "C"
JNIEXPORT jobject JNICALL
Java_com_nativejni_jni_JNIConstructorClass_invokeAnimalConstructors(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/nativejni/Animal");
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("jniParrot");

    jobject animal = env->NewObject(cls, mid, str);

    return animal;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_nativejni_jni_JNIConstructorClass_allocObjectConstructors(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/nativejni/Animal");
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("jniLionKing");

    jobject animal = env->AllocObject(cls);
    env->CallNonvirtualVoidMethod(animal, cls, mid, str);

    return animal;
}