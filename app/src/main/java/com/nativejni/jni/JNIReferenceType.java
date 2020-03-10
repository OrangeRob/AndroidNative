package com.nativejni.jni;

public class JNIReferenceType {
    static {
        System.loadLibrary("native-ref");
    }

    public native String errorCacheLocalReference();
    public native String cacheWithGlobalReference();
    public native void useWeakGlobalReference();
}
