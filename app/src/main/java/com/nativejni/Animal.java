package com.nativejni;

import android.util.Log;

public class Animal {
    private static final String TAG = "Animal";
    protected String name;
    public static int num = 0;


    public Animal(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public static int getNum() {
        return num;
    }

    public void callInstanceMethod(int num) {
        Log.i(TAG, "call instance method and num is " + num);
    }

    public static String callStaticMethod(String str) {
        if( str != null )
            Log.i(TAG, "call static method with " + str);
        else
            Log.i(TAG, "call static method str is null.");

        return "";
    }

    public static String callStaticMethod(String[] strs, int num) {
        Log.i(TAG, "num = " + num);
        if( strs != null )
            for(String str : strs)
                Log.i(TAG, "str in array is " + str);

        return "";
    }
}
