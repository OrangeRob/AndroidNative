package com.nativejni.jni;

import com.nativejni.Animal;

public class JNIAccessMethod {
    static {
        System.loadLibrary("native-method");
    }

    public native void accessInstanceMethod(Animal animal);
    public native void accessStaticMethod(Animal animal);
}
