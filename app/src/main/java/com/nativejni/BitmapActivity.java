package com.nativejni;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.nativejni.jni.JNIBitmap;

public class BitmapActivity extends AppCompatActivity {
    static boolean initFlag = false;
    Bitmap mirrorBitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bitmap);

        final ImageView imageView = findViewById(R.id.bitmap);
        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.tifa);
        final JNIBitmap jniBitmap = new JNIBitmap();
        imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!initFlag) {
                    mirrorBitmap = bitmap;
                    initFlag = !initFlag;
                }
                mirrorBitmap = jniBitmap.callNativeMirrorBitmap(mirrorBitmap);
                imageView.setImageBitmap(mirrorBitmap);
            }
        });
    }
}
