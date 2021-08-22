#ifndef OPENGLPLAYGROUND_POLYGONS_H
#define OPENGLPLAYGROUND_POLYGONS_H

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define PI 3.14159
#define numVAOs 1
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

        int polygonID = 4; // set the ID of the polygon to draw
        int numVertices; // Number of vertices in the polygon

        // OpenGL requires these values be specified in arrays
        GLuint vao[numVAOs];
        GLuint vbo[numVBOs];

        GLuint shaderProgram;

        GLfloat lineVertices[3*2];
        GLfloat triangleVertices[3*2];
        GLfloat squareVertices[4*2];
        GLfloat hexagonVertices[6*2];
        GLfloat circleVertices[100*2];

        Utils utils;
};

#endif //OPENGLPLAYGROUND_POLYGONS_H
