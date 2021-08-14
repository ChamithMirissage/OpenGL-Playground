package com.example.openglplayground;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer {
    int whichSubApp = 0;

    public GLRenderer(Context context) {}

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        selectInit(whichSubApp);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        selectResize(whichSubApp, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        selectRender(whichSubApp);
    }

    public void selectInit(int subAppId){
        switch (subAppId){
            case 0:
                shaderInit();
                break;
            case 1:
                textureInit();
                break;
        }
    }

    public void selectResize(int subAppId, int width, int height){
        switch (subAppId){
            case 0:
                shaderResize(width, height);
                break;
            case 1:
                textureResize(width, height);
                break;
        }
    }

    public void selectRender(int subAppId){
        switch (subAppId){
            case 0:
                shaderRender();
                break;
            case 1:
                textureRender();
                break;
        }
    }

    public static native void shaderInit();
    public static native void textureInit();

    public static native void shaderResize(int width, int height);
    public static native void textureResize(int width, int height);

    public static native void shaderRender();
    public static native void textureRender();
}
