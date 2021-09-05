#ifndef OPENGLPLAYGROUND_RENDERTOTEXTURE_H
#define OPENGLPLAYGROUND_RENDERTOTEXTURE_H

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../Utils/ShaderUtils.h"
#include "../Utils/TextureUtils.h"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define numVAOs 2
#define numVBOs 3

class RenderToTexture{
    public:
        void init();
        void resize(int width, int height);
        void render();

    private:
        int screenWidth;
        int screenHeight;

        GLuint VAO[numVAOs];
        GLuint VBO[numVBOs];

        GLuint FBO;
        GLuint renderingTextureID;

        GLuint shaderProgram;
        GLuint simpleTextureID;

        // Vertices of rectangles
        const GLfloat smallRectangleVertices[8] = {0.0, 0.75,
                                                   0.0, 0.0,
                                                   -0.75, 0.0,
                                                   -0.75, 0.75};
        const GLfloat largeRectangleVertices[8] = {0.5, 0.5,
                                                   0.5, -0.5,
                                                   -0.5, -0.5,
                                                   -0.5, 0.5};
        // Texture coordinates
        const GLfloat textureCoordinates[8] = {1.0, 1.0,  // Top right
                                               1.0, 0.0,  // Bottom right
                                               0.0, 0.0,  // Bottom left
                                               0.0, 1.0}; // Top left

        // Vertex shader
        const char* glVertexShader =
                "#version 310 es\n"
                "layout (location = 0) in vec4 vPosition;\n"
                "layout (location = 1) in vec2 vTextureCord;\n"
                "out vec2 textureCord;\n"
                "void main(){\n"
                "  gl_Position = vPosition;\n"
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

#endif //OPENGLPLAYGROUND_RENDERTOTEXTURE_H
