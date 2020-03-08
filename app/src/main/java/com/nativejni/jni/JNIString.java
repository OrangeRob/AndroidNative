package com.nativejni.jni;

public class JNIString {
    static {
        System.loadLibrary("native-string");
    }

    public native String callNativeString(String str);
    public native void stringMethod(String str);
}
