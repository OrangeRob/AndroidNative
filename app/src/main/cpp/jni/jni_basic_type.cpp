#include <base.h>

extern "C"
JNIEXPORT jint JNICALL Java_com_nativejni_jni_JNIBasicType_callNativeInt(JNIEnv *env, jobject thiz, jint num) {
    LOGD("java int value is %d", num);
    jint res = num*2;
    return res;
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeByte(JNIEnv *env, jobject thiz, jbyte b) {
    LOGD("java byte value is %d", b);
    jbyte res = b + (jbyte)10;
    return res;
}

extern "C"
JNIEXPORT jchar JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeChar(JNIEnv *env, jobject thiz, jchar ch) {
    LOGD("java char value is %c", ch);
    jchar res = ch + (jchar)3;
    return res;
}
extern "C"
JNIEXPORT jshort JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeShort(JNIEnv *env, jobject thiz, jshort sh) {
    LOGD("java short value is %d", sh);
    jshort res = sh + (jshort)10;
    return res;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeLong(JNIEnv *env, jobject thiz, jlong l) {
    LOGD("java long value is %lld", l);
    jlong res = l + 100;
    return res;
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeFloat(JNIEnv *env, jobject thiz, jfloat f) {
    LOGD("java float value is %f", f);
    jfloat res = f + (jfloat)10.0;
    return res;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeDouble(JNIEnv *env, jobject thiz, jdouble d) {
    LOGD("java double value is %f", d);
    jdouble res = d + 20.0;
    return res;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_nativejni_jni_JNIBasicType_callNativeBoolean(JNIEnv *env, jobject thiz, jboolean value) {
    LOGD("java boolean value is %d", value);
    jboolean res = (jboolean)!value;
    return res;
}
