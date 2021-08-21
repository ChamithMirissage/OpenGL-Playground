#ifndef OPENGLPLAYGROUND_SHADER_H
#define OPENGLPLAYGROUND_SHADER_H

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOG_TAG    "Shader"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class Shader{
    public:
        void init();
        void resize(int width, int height);
        void render();

    protected:
        glm::mat4 projection;
        glm::mat4 model;
        glm::mat4 view;

        GLuint shaderProgram;

        Utils utils;
};

#endif //OPENGLPLAYGROUND_SHADER_H
