#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIAccessField_accessInstanceField(JNIEnv *env, jobject thiz,
                                                          jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jstring str = env->NewStringUTF("bird");
    env->SetObjectField(animal, fid, str);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIAccessField_accessStaticField(JNIEnv *env, jobject thiz, jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetStaticFieldID(cls, "num", "I");
    int num = env->GetStaticIntField(cls, fid);
    LOGD("num from java : %d", num);
    env->SetStaticIntField(cls, fid, ++num);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nativejni_jni_JNIAccessField_staticAccessInstanceField(JNIEnv *env, jclass clazz) {
    jfieldID fid = env->GetStaticFieldID(clazz, "num", "I");
    int num = env->GetStaticIntField(clazz, fid);
    LOGD("num from java : %d", num);
    num++;
    env->SetStaticIntField(clazz, fid, num);
}

