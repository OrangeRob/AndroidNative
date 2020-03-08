package com.nativejni.jni;

import com.nativejni.interfaces.ICallbackMethod;
import com.nativejni.interfaces.IThreadCallback;

public class JNIInvokeMethod {
    static {
        System.loadLibrary("native-invoke");
    }

    public native void nativeCallback(ICallbackMethod callback);
    public native void nativeThreadCallback(IThreadCallback callback);
}
