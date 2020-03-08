package com.nativejni;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.nativejni.interfaces.ICallbackMethod;
import com.nativejni.interfaces.IThreadCallback;
import com.nativejni.jni.JNIAccessField;
import com.nativejni.jni.JNIAccessMethod;
import com.nativejni.jni.JNIBasicType;
import com.nativejni.jni.JNIConstructorClass;
import com.nativejni.jni.JNIDynamicLoad;
import com.nativejni.jni.JNIInvokeMethod;
import com.nativejni.jni.JNIReferenceType;
import com.nativejni.jni.JNIString;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Button btn_dynamic = findViewById(R.id.btn_dynamic);
        final Button btn_basic = findViewById(R.id.btn_basic);
        final Button btn_string = findViewById(R.id.btn_string);
        final Button btn_ref = findViewById(R.id.btn_reference);
        final Button btn_field = findViewById(R.id.btn_field);
        final Button btn_method = findViewById(R.id.btn_method);
        final Button btn_invoke = findViewById(R.id.btn_invoke);
        final Button btn_constructor = findViewById(R.id.btn_constructor);

        btn_dynamic.setOnClickListener(this);
        btn_basic.setOnClickListener(this);
        btn_string.setOnClickListener(this);
        btn_ref.setOnClickListener(this);
        btn_field.setOnClickListener(this);
        btn_method.setOnClickListener(this);
        btn_invoke.setOnClickListener(this);
        btn_constructor.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        final Animal animal = new Animal("dog");
        switch (v.getId()) {
            case R.id.btn_dynamic:
                final JNIDynamicLoad jniDynamicLoad = new JNIDynamicLoad();
                Log.i(TAG, "jni return string : " + jniDynamicLoad.getNativeString());
                Log.i(TAG, "jni sum = " + jniDynamicLoad.sum(4, 5));
                break;
            case R.id.btn_basic:
                final JNIBasicType jniBasicType = new JNIBasicType();
                Log.i(TAG, "java show : " + jniBasicType.callNativeInt(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeByte((byte)2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeChar('A'));
                Log.i(TAG, "java show : " + jniBasicType.callNativeShort((short)2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeLong(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeFloat(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeDouble(2));
                Log.i(TAG, "java show : " + jniBasicType.callNativeBoolean(false));
                break;
            case R.id.btn_string:
                final JNIString jniString = new JNIString();
                Log.i(TAG, "java show : " + jniString.callNativeString("This message from java."));
                jniString.stringMethod("This message from java.");
                break;
            case R.id.btn_reference:
                final String[] strArray = {"apple", "pear", "banana"};
                final JNIReferenceType jniReferenceType = new JNIReferenceType();
                Log.i(TAG, "array item is [" + jniReferenceType.callNativeStringArray(strArray) + "]");
                break;
            case R.id.btn_field:
                final JNIAccessField jniAccessField = new JNIAccessField();
                Log.i(TAG, "java > Animal name : " + animal.getName());
                Log.i(TAG, "java > Animal num : " + animal.getNum());
                jniAccessField.accessStaticField(animal);
                jniAccessField.accessInstanceField(animal);
                JNIAccessField.staticAccessInstanceField();
                Log.i(TAG, "jni > Animal name : " + animal.getName());
                Log.i(TAG, "jni > Animal num : " + animal.getNum());
                Log.i(TAG, "jni > JNIAccessField num : " + JNIAccessField.num);
                break;
            case R.id.btn_method:
                final JNIAccessMethod jniAccessMethod = new JNIAccessMethod();
                jniAccessMethod.accessInstanceMethod(animal);
                jniAccessMethod.accessStaticMethod(animal);
                break;
            case R.id.btn_invoke:
                final JNIInvokeMethod jniInvokeMethod = new JNIInvokeMethod();
                jniInvokeMethod.nativeCallback(new ICallbackMethod() {
                    @Override
                    public void callback() {
                        Log.i(TAG, "Thread name is : " + Thread.currentThread().getName());
                    }
                });

                jniInvokeMethod.nativeThreadCallback(new IThreadCallback() {
                    @Override
                    public void callback() {
                        Log.i(TAG, "Thread name is : " + Thread.currentThread().getName());
                    }
                });
                break;
            case R.id.btn_constructor:
                final JNIConstructorClass jniConstructorClass = new JNIConstructorClass();
                Log.i(TAG, "name is : " + jniConstructorClass.invokeAnimalConstructors().getName());
                Log.i(TAG, "name is : " + jniConstructorClass.allocObjectConstructors().getName());
                break;
        }
    }
}
