package com.nativejni;

import android.content.Intent;
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
import com.nativejni.jni.JNIException;
import com.nativejni.jni.JNIInvokeMethod;
import com.nativejni.jni.JNIReferenceType;
import com.nativejni.jni.JNIStringType;
import com.nativejni.jni.JNIThread;
import com.nativejni.jni.JNIWaitNotify;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn_dynamic = findViewById(R.id.btn_dynamic);
        Button btn_basic = findViewById(R.id.btn_basic);
        Button btn_string = findViewById(R.id.btn_string);
        Button btn_ref = findViewById(R.id.btn_reference);
        Button btn_field = findViewById(R.id.btn_field);
        Button btn_method = findViewById(R.id.btn_method);
        Button btn_invoke = findViewById(R.id.btn_invoke);
        Button btn_constructor = findViewById(R.id.btn_constructor);
        Button btn_exception = findViewById(R.id.btn_exception);
        Button btn_thread = findViewById(R.id.btn_thread);
        Button btn_thread_args = findViewById(R.id.btn_thread_args);
        Button btn_thread_join = findViewById(R.id.btn_thread_join);
        Button btn_thread_lock = findViewById(R.id.btn_thread_lock);
        Button btn_thread_notify = findViewById(R.id.btn_thread_notify);
        Button btn_thread_store = findViewById(R.id.btn_thread_store);
        Button btn_next_activity = findViewById(R.id.btn_next_activity);

        btn_dynamic.setOnClickListener(this);
        btn_basic.setOnClickListener(this);
        btn_string.setOnClickListener(this);
        btn_ref.setOnClickListener(this);
        btn_field.setOnClickListener(this);
        btn_method.setOnClickListener(this);
        btn_invoke.setOnClickListener(this);
        btn_constructor.setOnClickListener(this);
        btn_exception.setOnClickListener(this);
        btn_thread.setOnClickListener(this);
        btn_thread_args.setOnClickListener(this);
        btn_thread_join.setOnClickListener(this);
        btn_thread_lock.setOnClickListener(this);
        btn_thread_notify.setOnClickListener(this);
        btn_thread_store.setOnClickListener(this);
        btn_next_activity.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        Animal animal = new Animal("dog");
        switch (v.getId()) {
            case R.id.btn_dynamic:
                JNIDynamicLoad jniDynamicLoad = new JNIDynamicLoad();
                Log.i(TAG, "jni return string : " + jniDynamicLoad.getNativeString());
                Log.i(TAG, "jni sum = " + jniDynamicLoad.sum(4, 5));
                break;
            case R.id.btn_basic:
                JNIBasicType jniBasicType = new JNIBasicType();
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
                JNIStringType jniStringType = new JNIStringType();
                Log.i(TAG, "java show : " + jniStringType.callNativeString("This message from java."));
                jniStringType.stringMethod("This message from java.");

                String[] strArray = {"apple", "pear", "banana"};
                strArray = jniStringType.callNativeStringArray(strArray);
                for(String item : strArray)
                    Log.i(TAG, item);
                break;
            case R.id.btn_reference:
                JNIReferenceType jniReferenceType = new JNIReferenceType();
                System.out.println("use local Reference: " + jniReferenceType.errorCacheLocalReference());
                System.out.println("use global Reference: " + jniReferenceType.cacheWithGlobalReference());
                jniReferenceType.useWeakGlobalReference();
                break;
            case R.id.btn_field:
                JNIAccessField jniAccessField = new JNIAccessField();
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
                JNIAccessMethod jniAccessMethod = new JNIAccessMethod();
                jniAccessMethod.accessInstanceMethod(animal);
                jniAccessMethod.accessStaticMethod(animal);
                break;
            case R.id.btn_invoke:
                JNIInvokeMethod jniInvokeMethod = new JNIInvokeMethod();
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
                JNIConstructorClass jniConstructorClass = new JNIConstructorClass();
                Log.i(TAG, "name is : " + jniConstructorClass.invokeAnimalConstructors().getName());
                Log.i(TAG, "name is : " + jniConstructorClass.allocObjectConstructors().getName());
                break;
            case R.id.btn_exception:
                JNIException jniException = new JNIException();
                jniException.nativeInvokeJavaExecption();

                try {
                    jniException.nativeThrowExecption();
                } catch (IllegalArgumentException e) {
                    Log.i(TAG, e.getMessage());
                }
                break;
            case R.id.btn_thread:
                JNIThread jniThread = new JNIThread();
                jniThread.createNativeThread();
                break;
            case R.id.btn_thread_args:
                JNIThread jniThreadArgs = new JNIThread();
                jniThreadArgs.createNativeThreadWithArgs();
                break;
            case R.id.btn_thread_join:
                JNIThread jniThreadjoin = new JNIThread();
                jniThreadjoin.joinNativeThread();
                break;
            case R.id.btn_thread_lock:
                JNIWaitNotify jniLock = new JNIWaitNotify();
                jniLock.waitNativeThread();
                break;
            case R.id.btn_thread_notify:
                JNIWaitNotify jniNotify = new JNIWaitNotify();
                jniNotify.notifyNativeThread();
                break;
            case R.id.btn_thread_store:
                JNIWaitNotify jniStore = new JNIWaitNotify();
                jniStore.startProductAndConsumerThread();
                break;
            case R.id.btn_next_activity:
                startActivity(new Intent(MainActivity.this, BitmapActivity.class));
                break;
        }
    }
}
