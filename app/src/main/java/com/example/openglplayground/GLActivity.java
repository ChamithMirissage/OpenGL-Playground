package com.example.openglplayground;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class GLActivity extends AppCompatActivity {
    public static GLView glView;

    static {
        System.loadLibrary("opengl-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        glView = new GLView(this);
        setContentView(glView);
    }
}
