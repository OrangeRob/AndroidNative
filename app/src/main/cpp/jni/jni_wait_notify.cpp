#include <base.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <queue>

pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t waitHandle;
pthread_t notifyHandle;
static bool flag = false;

void *waitThread(void *) {
    LOGI("[wait] wait thread lock");
    pthread_mutex_lock(&mutex);

    while(!flag) {
        LOGI("[wait] wait cond....");
        pthread_cond_wait(&cond, &mutex);
    }

    LOGI("[wait] wait thread unlock");
    flag = false;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

void *notifyThread(void *) {
    LOGW("[notify] notify thread lock");
    pthread_mutex_lock(&mutex);
    flag = true;

    LOGW("[notify] notify thread unlock");
    pthread_mutex_unlock(&mutex);


    LOGW("[notify] send signal...");
    pthread_cond_signal(&cond);

    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIWaitNotify_waitNativeThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&waitHandle, nullptr, waitThread, nullptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIWaitNotify_notifyNativeThread(JNIEnv *env, jobject thiz) {
    pthread_create(&notifyHandle, nullptr, notifyThread, nullptr);
}

pthread_mutex_t dataMutex;
pthread_cond_t dataCond;
std::queue<int> data;

void *productThread(void *) {
    while( data.size() < 10 ) {
        pthread_mutex_lock(&dataMutex);
        LOGE("make product.");
        data.push(1);
        if( data.size() > 0 ) {
            LOGE("wait someone to buy product, number: %d", data.size());
            pthread_cond_signal(&dataCond);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(3);
    }
    pthread_exit(0);
}

void *consumerThread(void *) {
    while(1) {
        pthread_mutex_lock(&dataMutex);
        if(data.size() > 0) {
            LOGD("Buy product");
            data.pop();
            LOGD("product leaves: %d", data.size());
        } else {
            LOGD("Wait product");
            pthread_cond_wait(&dataCond, &dataMutex);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(1);
    }
    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIWaitNotify_startProductAndConsumerThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&dataMutex, nullptr);
    pthread_cond_init(&dataCond, nullptr);

    pthread_t productHandle;
    pthread_t consumerHandle;

    pthread_create(&productHandle, nullptr, productThread, nullptr);
    pthread_create(&consumerHandle, nullptr, consumerThread, nullptr);
}
