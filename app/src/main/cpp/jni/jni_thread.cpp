#include <base.h>
#include <pthread.h>
#include <unistd.h>

typedef struct _ThreadRunArgs {
    int id;
    int result;
} ThreadRunArgs;

void *printThreadHello(void *) {
    LOGW("[Cpp] hello thread.");
    pthread_exit(0);
}

void *printThreadArgs(void *args) {
    ThreadRunArgs *data = static_cast<ThreadRunArgs *>(args);
    LOGW("[Cpp] thread id : %d", data->id);
    LOGW("[Cpp] thread result : %d", data->result);
    pthread_exit(0);
}

void *printThreadJoin(void *args) {
    ThreadRunArgs *data = static_cast<ThreadRunArgs *>(args);
    struct timeval start, end;

    gettimeofday(&start, nullptr);
    sleep(5);
    gettimeofday(&end, nullptr);
    data->result = end.tv_sec - start.tv_sec;
    LOGW("[Cpp] Time used is : %d", data->result);
    return reinterpret_cast<void *>(data->result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIThread_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t pid;
    int ret = pthread_create(&pid, nullptr, printThreadHello, nullptr);
    if(ret == 0)
        LOGD("create thread success.");
    else
        LOGD("create thread failed.");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIThread_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    pthread_t pid;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 666;
    args->result = 777;
    int ret = pthread_create(&pid, nullptr, printThreadArgs, args);
    if(ret == 0)
        LOGD("create thread success.");
    else
        LOGD("create thread failed.");
    delete args;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIThread_joinNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t pid;
    ThreadRunArgs *args = new ThreadRunArgs;
    int ret = pthread_create(&pid, nullptr, printThreadJoin, args);
    if(ret == 0)
        LOGD("create thread success.");
    else
        LOGD("create thread failed.");

    void *result = nullptr;
    pthread_join(pid, &result);
    LOGD("thread result : %d s", result);
    delete args;
}