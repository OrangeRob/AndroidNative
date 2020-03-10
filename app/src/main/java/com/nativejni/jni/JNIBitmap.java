package com.nativejni.jni;

import android.graphics.Bitmap;

public class JNIBitmap {
    static {
        System.loadLibrary("native-bitmap");
    }

    public native Bitmap callNativeMirrorBitmap(Bitmap bitmap);
}
