#ifndef OPENGLPLAYGROUND_TEXTURES_H
#define OPENGLPLAYGROUND_TEXTURES_H

#include <jni.h>
#include <android/log.h>
//#include <SOIL2/SOIL2.h>

#include <GLES3/gl31.h>

#include "../Utils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"
//#include "../../../../libs/SOIL2/src/SOIL2/SOIL2.h"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define numVAOs 1
#define numVBOs 2

class Texture{
    public:
        void init();
        void resize(int width, int height);
        void render();

        GLuint createSimpleTexture();

    protected:
        glm::mat4 projection;
        glm::mat4 model;
        glm::mat4 view;

        // OpenGL requires these values be specified in arrays
        GLuint vao[numVAOs];
        GLuint vbo[numVBOs];

        GLuint shaderProgram;
        GLuint simpleTextureID;

        Utils utils;
};

#endif //OPENGLPLAYGROUND_TEXTURES_H
