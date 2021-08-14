package com.example.openglplayground;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer {
    public GLRenderer(Context context) {}

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        //init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        //resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        //render();
    }

    //public static native void init();
    //public static native void resize(int width, int height);
    //public static native void render();
}
