#include "Textures.h"

Texture textureObj;

void Texture::init(){

}

void Texture::resize(int width, int height){

}

void Texture::render(){

}

extern "C" {

void Java_com_example_openglplayground_GLRenderer_textureInit(JNIEnv *env, jclass obj) {
    textureObj.init();
}

void Java_com_example_openglplayground_GLRenderer_textureResize(JNIEnv *env, jclass obj, jint width, jint height) {
    textureObj.resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_textureRender(JNIEnv *env, jclass obj) {
    textureObj.render();
}

}