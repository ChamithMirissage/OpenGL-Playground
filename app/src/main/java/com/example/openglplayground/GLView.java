package com.example.openglplayground;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class GLView extends GLSurfaceView {
    GLRenderer glRenderer;

    public GLView(Context context) {
        super(context);
        glRenderer = new GLRenderer(context);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        setRenderer(glRenderer);
        setPreserveEGLContextOnPause(true);
    }
}
