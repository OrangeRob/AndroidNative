package com.nativejni.jni;

public class JNIThread {
    static {
        System.loadLibrary("native-thread");
    }

    public native void createNativeThread();
    public native void createNativeThreadWithArgs();
    public native void joinNativeThread();
}
