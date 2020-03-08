#include <base.h>
#include <jvm.h>
#include <pthread.h>

static jclass threadClass;
static jmethodID threadMID;
static jobject threadObject;

void *threadCallback(void *);

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIInvokeMethod_nativeCallback(JNIEnv *env, jobject thiz, jobject callback) {
    LOGD("native callback");
    jclass callbackClass = env->GetObjectClass(callback);
    jmethodID mid = env->GetMethodID(callbackClass, "callback", "()V");
    env->CallVoidMethod(callback, mid);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIInvokeMethod_nativeThreadCallback(JNIEnv *env, jobject thiz,
                                                            jobject callback) {
    threadObject = env->NewGlobalRef(callback);
    threadClass = env->GetObjectClass(callback);
    threadMID = env->GetMethodID(threadClass, "callback", "()V");

    pthread_t handle;
    pthread_create(&handle, nullptr, threadCallback, nullptr);
}

void *threadCallback(void *) {
    JavaVM *vm = getJVM();
    JNIEnv *env = nullptr;
    if( vm->AttachCurrentThread(&env, nullptr) == 0 ) {
        env->CallVoidMethod(threadObject, threadMID);
        vm->DetachCurrentThread();
    }

    return 0;
}

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD(">>>>> JNI_OnLoad");
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    setJVM(vm);

    return JNI_VERSION_1_6;
}