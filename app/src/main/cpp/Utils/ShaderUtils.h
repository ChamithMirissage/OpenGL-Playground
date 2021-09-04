#ifndef OPENGLPLAYGROUND_SHADERUTILS_H
#define OPENGLPLAYGROUND_SHADERUTILS_H

#include <jni.h>
#include <malloc.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#define  LOG_TAG    "openglPlayground"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class ShaderUtils{
    public:
        static GLuint loadShader(GLenum shaderType, const char *shaderSource) {
            GLuint shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &shaderSource, nullptr);
            glCompileShader(shader);

            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled){
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen){
                    char *buf = (char *) malloc(infoLen);
                    if (buf){
                        glGetShaderInfoLog(shader, infoLen, nullptr, buf);
                        LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                        free(buf);
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
            return shader;
        }

        static GLuint createShaderProgram(const char *vertexSource, const char *fragmentSource) {
            GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
            GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
            GLuint program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            GLint linked = GL_FALSE;
            glGetProgramiv(program , GL_LINK_STATUS, &linked);
            if (linked != GL_TRUE){
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength){
                    char* buf = (char*) malloc(bufLength);
                    if (buf){
                        glGetProgramInfoLog(program, bufLength, nullptr, buf);
                        LOGE("Could not link program:\n%s\n", buf);
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
            return program;
        }
};

#endif //OPENGLPLAYGROUND_SHADERUTILS_H
