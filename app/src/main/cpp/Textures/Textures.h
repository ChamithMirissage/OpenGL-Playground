#ifndef OPENGLPLAYGROUND_TEXTURES_H
#define OPENGLPLAYGROUND_TEXTURES_H

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOG_TAG    "texture"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class Texture{
    public:
        void init();
        void resize(int width, int height);
        void render();

        GLuint loadSimpleTexture();

    protected:
        glm::mat4 projection;
        glm::mat4 model;
        glm::mat4 view;

        GLuint shaderProgram;
        GLuint simpleTextureID;

        Utils utils;
};

#endif //OPENGLPLAYGROUND_TEXTURES_H
