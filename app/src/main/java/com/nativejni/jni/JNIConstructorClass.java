package com.nativejni.jni;

import com.nativejni.Animal;

public class JNIConstructorClass {
    static {
        System.loadLibrary("native-constructor");
    }

    public native Animal invokeAnimalConstructors();
    public native Animal allocObjectConstructors();
}
