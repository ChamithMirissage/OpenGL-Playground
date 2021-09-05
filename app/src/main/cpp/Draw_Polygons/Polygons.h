#ifndef OPENGLPLAYGROUND_POLYGONS_H
#define OPENGLPLAYGROUND_POLYGONS_H

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils/ShaderUtils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define PI 3.14159
#define numVBOs 1

class Polygons{
    public:
        void init();
        void resize(int width, int height);
        void render();

        void setLineVertices();
        void setTriangleVertices();
        void setSquareVertices();
        void setHexagonVertices();
        void setCircleVertices();
        void selectPolygon(int polyID);

    protected:
        glm::mat4 projection;
        glm::mat4 model;
        glm::mat4 view;

        int polygonID = 2; // set the ID of the polygon to draw
        int numVertices; // Number of vertices in the polygon

        GLuint VAO;
        GLuint VBO[numVBOs];

        GLuint shaderProgram;

        GLfloat lineVertices[3*2];
        GLfloat triangleVertices[3*2];
        GLfloat squareVertices[4*2];
        GLfloat hexagonVertices[6*2];
        GLfloat circleVertices[100*2];

        // Vertex shader
        const char* glVertexShader =
                "#version 310 es\n"
                "uniform mat4 projection;\n"
                "uniform mat4 view;\n"
                "uniform mat4 model;\n"
                "layout (location = 0) in vec4 vPosition;\n"
                "void main(){\n"
                "  gl_Position = projection * view * model * vPosition;\n"
                "}\n";

        // Fragment shader
        const char* glFragmentShader =
                "#version 310 es\n"
                "precision mediump float;\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "  fragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
                "}\n";
};

#endif //OPENGLPLAYGROUND_POLYGONS_H
