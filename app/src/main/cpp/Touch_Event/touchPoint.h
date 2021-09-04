#ifndef OPENGLPLAYGROUND_TOUCHPOINT_H
#define OPENGLPLAYGROUND_TOUCHPOINT_H

#include <jni.h>
#include <vector>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils/ShaderUtils.h"
#include "../Utils/TextureUtils.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace std;

class TouchPoint{
    public:
        void init();
        void resize(int width, int height);
        void render(float x, float y, int actionUp);

    protected:
        int index = 0;
        int numPoints = 0;
        int screenWidth;
        int screenHeight;

        vector<GLint> touchIndices;
        vector<GLfloat> touchPoints;

        GLuint vao;
        GLuint vbo;
        GLuint ebo;

        GLuint shaderProgram;
        GLuint simpleTextureID;

        // Vertex shader
        const char* glVertexShader =
                "#version 310 es\n"
                "layout (location = 0) in vec4 vPosition;\n"
                "void main(){\n"
                "  gl_PointSize = 20.0;\n"
                "  gl_Position = vPosition;\n"
                "}\n";

        // Fragment shader
        const char* glFragmentShader =
                "#version 310 es\n"
                "precision mediump float;\n"
                "layout (binding = 0) uniform sampler2D textureIn;\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "   fragColor = texture(textureIn, gl_PointCoord);\n"
                "}\n";
};

#endif //OPENGLPLAYGROUND_TOUCHPOINT_H