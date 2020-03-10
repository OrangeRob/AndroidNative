package com.nativejni.jni;

public class JNIException {
    static {
        System.loadLibrary("native-execption");
    }

    private int operation() {
        return 2 / 0;
    }

    public native void nativeInvokeJavaExecption();
    public native void nativeThrowExecption() throws IllegalArgumentException;

}
