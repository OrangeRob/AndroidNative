package com.nativejni.jni;

public class JNIReferenceType {
    static {
        System.loadLibrary("native-ref");
    }

    public native String callNativeStringArray(String[] strArray);
}
