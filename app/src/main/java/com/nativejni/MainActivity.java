package com.nativejni;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.nativejni.jni.JNIAccessField;
import com.nativejni.jni.JNIAccessMethod;
import com.nativejni.jni.JNIBasicType;
import com.nativejni.jni.JNIDynamicLoad;
import com.nativejni.jni.JNIReferenceType;
import com.nativejni.jni.JNIString;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final JNIDynamicLoad jniDynamicLoad = new JNIDynamicLoad();
        final Button btn_dynamic = findViewById(R.id.btn_dynamic);
        btn_dynamic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "jni return string : " + jniDynamicLoad.getNativeString());
                Log.i(TAG, "jni sum = " + jniDynamicLoad.sum(4, 5));
            }
        });

        final JNIBasicType jniBasicType = new JNIBasicType();
        final Button btn_basic = findViewById(R.id.btn_basic);
        btn_basic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "java show : " + jniBasicType.callNativeInt(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeByte((byte)2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeChar('A'));
                Log.i(TAG, "java show : " + jniBasicType.callNativeShort((short)2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeLong(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeFloat(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeDouble(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeBoolean(false));

            }
        });

        final JNIString jniString = new JNIString();
        final Button btn_string = findViewById(R.id.btn_string);
        btn_string.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "java show : " + jniString.callNativeString("This message from java."));
                jniString.stringMethod("This message from java.");
            }
        });

        final String[] strArray = {"apple", "pear", "banana"};
        final JNIReferenceType jniReferenceType = new JNIReferenceType();
        final Button btn_ref = findViewById(R.id.btn_reference);
        btn_ref.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "array item is [" + jniReferenceType.callNativeStringArray(strArray) + "]");
            }
        });

        final Animal animal = new Animal("dog");
        final JNIAccessField jniAccessField = new JNIAccessField();
        final Button btn_field = findViewById(R.id.btn_field);
        btn_field.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "java > Animal name : " + animal.getName());
                Log.i(TAG, "java > Animal num : " + animal.getNum());
                jniAccessField.accessStaticField(animal);
                jniAccessField.accessInstanceField(animal);
                JNIAccessField.staticAccessInstanceField();
                Log.i(TAG, "jni > Animal name : " + animal.getName());
                Log.i(TAG, "jni > Animal num : " + animal.getNum());
                Log.i(TAG, "jni > JNIAccessField num : " + JNIAccessField.num);
            }
        });

        final JNIAccessMethod jniAccessMethod = new JNIAccessMethod();
        final Button btn_method = findViewById(R.id.btn_method);
        btn_method.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jniAccessMethod.accessInstanceMethod(animal);
                jniAccessMethod.accessStaticMethod(animal);
            }
        });

    }
}
