#ifndef OPENGLPLAYGROUND_SHADER_H
#define OPENGLPLAYGROUND_SHADER_H

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils/ShaderUtils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define numVBOs 2

class Shader{
    public:
        void init();
        void resize(int width, int height);
        void render();

    protected:
        glm::mat4 projection;
        glm::mat4 model;
        glm::mat4 view;

        GLuint VAO;
        GLuint VBO[numVBOs];

        GLuint shaderProgram;

        // Details of the square
        const GLfloat squareVertices[8] = {0.5, 0.5,
                                           0.5, -0.5,
                                           -0.5, -0.5,
                                           -0.5, 0.5};
        const GLfloat squareVertexColors[12] = {1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 1.0, 0.0};

        // Vertex shader
        const char* glVertexShader =
                "#version 310 es\n"
                "uniform mat4 projection;\n"
                "uniform mat4 view;\n"
                "uniform mat4 model;\n"
                "layout (location = 0) in vec4 vPosition;\n"
                "layout (location = 1) in vec4 vColor;\n"
                "out vec4 vertexColor;\n"
                "void main(){\n"
                "  gl_Position = projection * view * model * vPosition;\n"
                "  vertexColor = vColor;\n"
                "}\n";

        // Fragment shader
        const char* glFragmentShader =
                "#version 310 es\n"
                "precision mediump float;\n"
                "in vec4 vertexColor;\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "  fragColor = vertexColor;\n"
                "}\n";
};

#endif //OPENGLPLAYGROUND_SHADER_H
