package com.unity3d.player;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class UnityPlayerActivity extends Activity {

    public boolean onTouchEvent(MotionEvent motionEvent) {
        return true;
    }
    public boolean dispatchKeyEvent(KeyEvent motionEvent) {
        return true;
    }

    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
    }
}
