#include "Utils.h"

GLuint Utils::loadShader(GLenum shaderType, const char *shaderSource) {
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

GLuint Utils::createShaderProgram(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShader = this->loadShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = this->loadShader(GL_FRAGMENT_SHADER, fragmentSource);
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

