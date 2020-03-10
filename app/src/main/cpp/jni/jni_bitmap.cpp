#include <base.h>
#include <android/bitmap.h>
#include <cstring>
#include <charconv>

jobject generateBitmap(JNIEnv *env, uint32_t width, uint32_t height) {
    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapFunction = env->GetStaticMethodID(bitmapCls, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOfBitmapConfigFunction = env->GetStaticMethodID(bitmapConfigClass, "valueOf", "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");

    jobject bitmapConfig = env->CallStaticObjectMethod(bitmapConfigClass, valueOfBitmapConfigFunction, configName);
    jobject resBitmap = env->CallStaticObjectMethod(bitmapCls, createBitmapFunction, width, height, bitmapConfig);
    return resBitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_nativejni_jni_JNIBitmap_callNativeMirrorBitmap(JNIEnv *env, jobject thiz, jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

    LOGD("bitmap width = %d, height = %d", bitmapInfo.width, bitmapInfo.height);

    void *bitmapPixels;
    AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels);
    uint32_t newWidth = bitmapInfo.width;
    uint32_t newHeight = bitmapInfo.height;
    uint32_t *mirrorBitmapPixels = new uint32_t[newWidth * newHeight];

    /* mirror processing */
    int position = 0;
    for(int y = 0; y < newHeight; y++) {
        for(int x = newWidth - 1; x >= 0; x--) {
            uint32_t pixel = ((uint32_t *)bitmapPixels)[position++];
            mirrorBitmapPixels[newWidth * y + x] = pixel;
        }
    }
    AndroidBitmap_unlockPixels(env, bitmap);

    /* set return bitmap */
    jobject retBitmap = generateBitmap(env, newWidth, newHeight);
    void *resultBitmapPixels;
    AndroidBitmap_lockPixels(env, retBitmap, &resultBitmapPixels);
    memcpy((uint32_t *)resultBitmapPixels, mirrorBitmapPixels, sizeof(uint32_t)*newWidth*newHeight);
    AndroidBitmap_unlockPixels(env, retBitmap);

    delete[] mirrorBitmapPixels;
    return retBitmap;
}

