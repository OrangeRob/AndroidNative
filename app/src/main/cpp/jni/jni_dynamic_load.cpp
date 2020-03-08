#include <base.h>

jstring getMessage(JNIEnv* env, jobject thiz) {
    return env->NewStringUTF("this is message from jni");
}

jint plus(JNIEnv* env, jobject thiz, int x, int y) {
    return x + y;
}

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // Find your class. JNI_OnLoad is called from the correct class loader context for this to work.
    jclass jcls = env->FindClass("com/nativejni/jni/JNIDynamicLoad");
    if (jcls == nullptr) return JNI_ERR;

    // Register your class' native methods.
    static const JNINativeMethod methods[] = {
            {"sum", "(II)I", reinterpret_cast<void*>(plus)},
            {"getNativeString", "()Ljava/lang/String;", reinterpret_cast<void*>(getMessage)},
    };

    int rc = env->RegisterNatives(jcls, methods, sizeof(methods)/sizeof(JNINativeMethod));
    if (rc != JNI_OK) return rc;
    LOGD(">>>>> jni onload successful.");
    return JNI_VERSION_1_6;
}

