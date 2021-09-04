package com.example.openglplayground;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer {
    /* Set whichSubApp to
    0 for run Shader.cpp
    1 for run Texture.cpp
    2 for run Polygons.cpp
    3 for run TouchPoint.cpp*/
    int whichSubApp = 3;

    float x, y;
    int actionUp = -1;
    boolean isTouch = false;

    public GLRenderer(Context context) {}

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        selectInit(this.whichSubApp);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        selectResize(this.whichSubApp, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        selectRender(this.whichSubApp);
    }

    public void setCords(float xPos, float yPos, int isActionUp){
        this.x = xPos;
        this.y = yPos;
        this.actionUp = isActionUp;
        this.isTouch = true;
    }

    public void selectInit(int subAppId){
        switch (subAppId){
            case 0:
                shaderInit();
                break;
            case 1:
                textureInit();
                break;
            case 2:
                polygonsInit();
                break;
            case 3:
                touchPointInit();
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
            case 2:
                polygonsResize(width, height);
                break;
            case 3:
                touchPointResize(width, height);
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
            case 2:
                polygonsRender();
                break;
            case 3:
                if (!this.isTouch){
                    this.actionUp = -1;
                }
                this.isTouch = false;
                touchPointRender(this.x, this.y, this.actionUp);
                break;
        }
    }

    public static native void shaderInit();
    public static native void textureInit();
    public static native void polygonsInit();
    public static native void touchPointInit();

    public static native void shaderResize(int width, int height);
    public static native void textureResize(int width, int height);
    public static native void polygonsResize(int width, int height);
    public static native void touchPointResize(int width, int height);

    public static native void shaderRender();
    public static native void textureRender();
    public static native void polygonsRender();
    public static native void touchPointRender(float x, float y, int actionUp);
}
