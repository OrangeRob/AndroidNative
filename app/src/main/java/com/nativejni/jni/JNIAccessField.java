package com.nativejni.jni;

import com.nativejni.Animal;

public class JNIAccessField {
    static {
        System.loadLibrary("native-field");
    }

    public static int num;

    public native void accessInstanceField(Animal animal);
    public native void accessStaticField(Animal animal);
    public static native void staticAccessInstanceField();
}
