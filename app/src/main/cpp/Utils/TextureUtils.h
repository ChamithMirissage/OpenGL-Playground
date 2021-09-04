#ifndef OPENGLPLAYGROUND_TEXTUREUTILS_H
#define OPENGLPLAYGROUND_TEXTUREUTILS_H

#include <jni.h>
#include <malloc.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#define  LOG_TAG    "openglPlayground"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class TextureUtils{
    public:
        static GLuint createSimpleTexture(){
            // Texture object handle
            GLuint textureId;
            // 3x3 image, RGBA channels raw format
            GLubyte data[9 * 4] =
                {
                    255, 0, 255, 255, // Some color bottom left
                    255, 0, 255, 255, // Some color bottom middle
                    255, 0, 255, 255, // Some color bottom right
                    255, 0, 255, 255, // Yellow middle left
                    255, 0, 255, 255, // Some color middle
                    255, 0, 255, 255, // Some color middle right
                    255, 0, 255, 255, // Red top left
                    255, 0, 255, 255, // Green top middle
                    255, 0, 255, 255  // Blue top right
                };
            // Generate a texture object
            glGenTextures(1, &textureId);
            // Make the texture object active
            glBindTexture(GL_TEXTURE_2D, textureId);
            // Associate the image data into the the texture object
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            // Set the filtering mode
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            return textureId;
        }
};

#endif //OPENGLPLAYGROUND_TEXTUREUTILS_H
