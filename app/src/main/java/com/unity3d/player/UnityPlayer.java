package com.unity3d.player;

import android.app.Activity;
import android.content.Context;
import android.view.InputEvent;
import android.view.KeyEvent;
import android.widget.FrameLayout;

public class UnityPlayer extends FrameLayout {
    public static Activity currentActivity;

    public boolean injectEvent(InputEvent inputEvent) {
        return false;
    }


    public UnityPlayer(Context context) {
        super(context);
        currentActivity = (Activity) context;
    }
}
