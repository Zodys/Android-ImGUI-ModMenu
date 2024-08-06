package com.zodys.gui;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import androidx.annotation.RequiresApi;

import com.unity3d.player.UnityPlayerActivity;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class MyUnityPlayerActivity extends UnityPlayerActivity {

    static {
        System.loadLibrary("zodys");
    }

    @RequiresApi(api = Build.VERSION_CODES.S)
    @Override
    public void onCreate(Bundle bundle) {
        requestWindowFeature(1);
        getWindow().setFlags(1024, 1204);
        super.onCreate(bundle);
        //Log.d("Arch",System.getProperty("os.arch"));
        //Loader.Load(this);
        setContentView(R.layout.activity_main);
        Surface.Start(this);
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent keyEvent) {
        //Log.d("Input",String.valueOf(Surface.Input(keyEvent)));

       /* if (!Surface.Input(keyEvent)) {

        }*/
        return super.dispatchKeyEvent(keyEvent);
    }

    @Override
    public boolean onTouchEvent(MotionEvent motionEvent) {
        //Log.d("Input",String.valueOf(Surface.Input(motionEvent)));
           /* if (!Surface.Input(motionEvent)) {

            }*/
        return super.onTouchEvent(motionEvent);
    }
}
