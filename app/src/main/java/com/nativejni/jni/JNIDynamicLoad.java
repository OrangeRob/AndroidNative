package com.nativejni.jni;

public class JNIDynamicLoad {
    static {
        System.loadLibrary("dynamic-lib");
    }

    public native int sum(int x, int y);
    public native String getNativeString();
}
