package com.nativejni.jni;

public class JNIWaitNotify {
    static {
        System.loadLibrary("native-notify");
    }

    public native void waitNativeThread();
    public native void notifyNativeThread();
    public native void startProductAndConsumerThread();
}
