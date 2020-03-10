#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIException_nativeInvokeJavaExecption(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/nativejni/jni/JNIException");
    jmethodID funMID = env->GetMethodID(cls, "operation", "()I");
    jmethodID constructorMID = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, constructorMID);

    env->CallIntMethod(obj, funMID);
    /*
     * ExceptionOccurred and ExceptionCheck check for pending exceptions in
     * the current thread.
     */
#ifndef _CHECK_EXECPTION_METHOD1_
    jthrowable err = env->ExceptionOccurred();
    if(err) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#else // _CHECK_EXECPTION_METHOD2_
    if(env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIException_nativeThrowExecption(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("java/lang/IllegalArgumentException");

    env->ThrowNew(cls, "[Cpp] native throw execption");

}