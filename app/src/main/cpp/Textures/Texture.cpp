#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOG_TAG    "texture"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
/*
void init(){

}

void resize(int width, int height){

}

void render(){

}
*/
extern "C" {

void Java_com_example_openglplayground_GLRenderer_textureInit(JNIEnv *env, jclass obj) {
    //init();
}

void Java_com_example_openglplayground_GLRenderer_textureResize(JNIEnv *env, jclass obj, jint width, jint height) {
    //resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_textureRender(JNIEnv *env, jclass obj) {
    //render();
}

}