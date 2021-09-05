#include "RenderToTexture.h"

RenderToTexture renderToTextureObj;

void RenderToTexture::init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Create a vertex array object(VAO)
    glGenVertexArrays(2, this->VAO);
    // Create a buffer object(VBO) for each attribute
    glGenBuffers(3, this->VBO);

    // Create the framebuffer(FBO) & rendering texture object
    glGenBuffers(1, &this->FBO);
    glGenTextures(1, &this->renderingTextureID);

    // Create the shader program
    this->shaderProgram = ShaderUtils::createShaderProgram(this->glVertexShader, this->glFragmentShader);
    // Create the texture and load it
    this->simpleTextureID = TextureUtils::createSimpleTexture();
}

void RenderToTexture::resize(int width, int height) {
    glViewport(0, 0, width, height);
    this->screenWidth = width;
    this->screenHeight = height;

    // Make the framebuffer active
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
    // Make the texture object active
    glBindTexture(GL_TEXTURE_2D, this->renderingTextureID);
    // Specify the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->screenWidth, this->screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
    // Attach the texture to framebuffer
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->renderingTextureID, 0);
    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderToTexture::render() {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    ///--- For small rectangle ---///
    // Make the VAO active
    glBindVertexArray(this->VAO[0]);

    // Make the 0th buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);
    // Copy the array containing vertices into the 0th buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->smallRectangleVertices), &this->smallRectangleVertices, GL_STATIC_DRAW);

    // Make the 1st buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]);
    // Copy the array containing texture coordinates into the 1st buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->textureCoordinates), &this->textureCoordinates, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);
    // Associate 0th attribute(defined in the vertex shader) with the 0th buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    // Enable the 0th vertex attribute
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    // Unbind the buffer and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    ///--- For large rectangle ---///
    glBindVertexArray(this->VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->largeRectangleVertices), &this->largeRectangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->textureCoordinates), &this->textureCoordinates, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[2]);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ///--- Render to texture ---///
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
    glUseProgram(this->shaderProgram);

    // Bind textureIn to texture unit 0
    GLint textureLocation = glGetUniformLocation(this->shaderProgram, "textureIn");
    glUniform1i(textureLocation, 0);

    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Activate the 0th texture unit
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, this->simpleTextureID);
    glBindVertexArray(this->VAO[0]);

    // Draw small rectangle in framebuffer
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(0);
    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ///--- Color large rectangle using rendered texture ---///
    glUseProgram(this->shaderProgram);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->renderingTextureID);
    glBindVertexArray(this->VAO[1]);

    // Draw large rectangle
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(0);
    glUseProgram(0);
}

extern "C" {

void Java_com_example_openglplayground_GLRenderer_renderToTextureInit(JNIEnv *env, jclass obj) {
    renderToTextureObj.init();
}

void Java_com_example_openglplayground_GLRenderer_renderToTextureResize(JNIEnv *env, jclass obj, jint width, jint height) {
    renderToTextureObj.resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_renderToTextureRender(JNIEnv *env, jclass obj) {
    renderToTextureObj.render();
}

}

