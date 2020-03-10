#include <base.h>
#include <cstring>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nativejni_jni_JNIReferenceType_errorCacheLocalReference(JNIEnv *env, jobject thiz) {
    jclass localRefs = env->FindClass("java/lang/String");
    jmethodID mid = env->GetMethodID(localRefs, "<init>", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("[Cpp] use local reference");

#ifdef _ERROR
    /* cause local reference table overflow */
    for(int i = 0; i < 10000000; i++) {
        jclass localRefs = env->FindClass("java/lang/String");
        env->DeleteLocalRef(localRefs);
    }
#endif

    return static_cast<jstring>(env->NewObject(localRefs, mid, str));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nativejni_jni_JNIReferenceType_cacheWithGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass globalRef = nullptr;
    if(globalRef == nullptr) {
        jclass cls = env->FindClass("java/lang/String");
        globalRef = static_cast<jclass>(env->NewGlobalRef(cls));
        env->DeleteLocalRef(cls);
        LOGD("jclass address : %p", globalRef);
    } else {
        LOGD("use cached. jclass address : %p", globalRef);
    }

    jmethodID mid = env->GetMethodID(globalRef, "<init>", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("[Cpp] use global reference");
    return static_cast<jstring>(env->NewObject(globalRef, mid, str));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIReferenceType_useWeakGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass weakGlobalRef = nullptr;
    jboolean isGC = env->IsSameObject(weakGlobalRef, nullptr);
    LOGD("weakGlobalRef exist ? %d (address : %p)", isGC, weakGlobalRef);
    if(weakGlobalRef == nullptr) {
        jclass cls = env->FindClass("java/lang/String");
        weakGlobalRef = static_cast<jclass>(env->NewWeakGlobalRef(cls)); // env->DeleteGlobalRef()
        env->DeleteLocalRef(cls);
    }
}