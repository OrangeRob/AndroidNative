package com.nativejni.jni;

public class JNIStringType {
    static {
        System.loadLibrary("native-string");
    }

    public native String callNativeString(String str);
    public native void stringMethod(String str);
    public native String[] callNativeStringArray(String[] strArray);
}
