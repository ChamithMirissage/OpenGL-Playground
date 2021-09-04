package com.example.openglplayground;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class GLView extends GLSurfaceView {
    GLRenderer glRenderer;
    int isActionUp = 1;

    public GLView(Context context) {
        super(context);
        this.glRenderer = new GLRenderer(context);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        setRenderer(this.glRenderer);
        setPreserveEGLContextOnPause(true);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e){
        float x, y;

        switch (e.getAction()){
            case MotionEvent.ACTION_DOWN:{
                Log.e("CCEView", "ACTION DOWN");
                break;
            }

            case MotionEvent.ACTION_MOVE:{
                x = e.getX();
                y = e.getY();
                this.isActionUp = 0;
                this.glRenderer.setCords(x, y, isActionUp);
                requestRender();
                break;
            }

            case MotionEvent.ACTION_UP:{
                Log.e("CCEView", "ACTION UP");
                break;
            }
        }
        return true;
    }
}
