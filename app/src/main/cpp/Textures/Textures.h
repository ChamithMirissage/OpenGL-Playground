#ifndef OPENGLPLAYGROUND_TEXTURES_H
#define OPENGLPLAYGROUND_TEXTURES_H

#include <jni.h>
#include <android/log.h>
//#include <SOIL2/SOIL2.h>

#include <GLES3/gl31.h>

#include "../Utils/ShaderUtils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"
//#include "../../../../libs/SOIL2/src/SOIL2/SOIL2.h"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

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
        GLuint vao;
        GLuint vbo[numVBOs];

        GLuint shaderProgram;
        GLuint simpleTextureID;

        // Details of the square
        const GLfloat squareVertices[8] = {0.5, 0.5,
                                           0.5, -0.5,
                                           -0.5, -0.5,
                                           -0.5, 0.5};

        const GLfloat textureCoordinates[8] = {1.0, 1.0,  // Top right
                                               1.0, 0.0,  // Bottom right
                                               0.0, 0.0,  // Bottom left
                                               0.0, 1.0}; // Top left

        // Vertex shader
        const char* glVertexShader =
                "#version 310 es\n"
                "uniform mat4 projection;\n"
                "uniform mat4 view;\n"
                "uniform mat4 model;\n"
                "layout (location = 0) in vec4 vPosition;\n"
                "layout (location = 1) in vec2 vTextureCord;\n"
                "out vec2 textureCord;\n"
                "void main(){\n"
                "  gl_Position = projection * view * model * vPosition;\n"
                "  textureCord = vTextureCord;\n"
                "}\n";

        // Fragment shader
        const char* glFragmentShader =
                "#version 310 es\n"
                "precision mediump float;\n"
                "layout (binding = 0) uniform sampler2D textureIn;\n"
                "in vec2 textureCord;\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "  fragColor = texture(textureIn, textureCord);\n"
                "}\n";
};

#endif //OPENGLPLAYGROUND_TEXTURES_H
