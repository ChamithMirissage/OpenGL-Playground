#ifndef OPENGLPLAYGROUND_UTILS_H
#define OPENGLPLAYGROUND_UTILS_H

#include <jni.h>
#include <malloc.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#define  LOG_TAG    "openglPlayground"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class Utils{
    public:
        GLuint loadShader(GLenum shaderType, const char *shaderSource);
        GLuint createShaderProgram(const char *vertexSource, const char *fragmentSource);
};

#endif //OPENGLPLAYGROUND_UTILS_H
