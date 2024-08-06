package com.zodys.gui;

import android.content.Context;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.opengl.GLSurfaceView;
import android.view.WindowManager;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class Surface extends GLSurfaceView implements GLSurfaceView.Renderer {
    private static Surface instance;
    private boolean Pause = false;
    private static int screenHeight, screenWidth;
    private native void DrawFrame();
    private native void ShutDown();
    private native void SurfaceCreated();
    private native void SurfaceChanged(int width, int height);


    public void onDrawFrame(GL10 gl10) {
        try {

            DrawFrame();
        } catch (UnsatisfiedLinkError unused) {
        }
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig eGLConfig) {
        try {

            SurfaceCreated();
        } catch (UnsatisfiedLinkError unused) {
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int i, int i1) {
        try {
            SurfaceChanged(i,i1);

        }catch (UnsatisfiedLinkError unused) {
        }
    }


    private Surface(Context context) {
        super(context);
        //Loader.LoadLibFromAssets(context, "lib");
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setZOrderOnTop(true);

        setRenderer(this);
    }

    public static void Start(Context context) {
        if (instance == null) {
            instance = new Surface(context);

            WindowManager windowManager = (WindowManager)context.getSystemService(Context.WINDOW_SERVICE);
            final Point screemSize = new Point();
            windowManager.getDefaultDisplay().getRealSize(screemSize);
            screenWidth = screemSize.x;
            screenHeight = screemSize.y;
            WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams(screenWidth, screenHeight, 0, 0, 2, 33686296, -2);
            //layoutParams.gravity = 8388659;
            windowManager.addView(instance, layoutParams);
        }
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        try {

            ShutDown();
        }catch (UnsatisfiedLinkError unused) {
        }

    }

    public void onPause() {
        super.onPause();
        this.Pause = true;
    }

    public void onResume() {
        super.onResume();
        this.Pause = false;
    }
}