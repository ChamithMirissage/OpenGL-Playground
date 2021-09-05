#include "touchPoint.h"

TouchPoint touchPointObj;

void TouchPoint::init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Create a vertex array object(VAO)
    glGenVertexArrays(1, &this->VAO);
    // Create buffer objects(VBO) for vertices and indices
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    // Create the shader program
    this->shaderProgram = ShaderUtils::createShaderProgram(glVertexShader, glFragmentShader);
    // Create the texture and load it
    this->simpleTextureID = TextureUtils::createSimpleTexture();
}

void TouchPoint::resize(int width, int height) {
    glViewport(0, 0, width, height);
    this->screenWidth = width;
    this->screenHeight = height;
}

void TouchPoint::render(float x, float y, int actionUp) {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    if (actionUp == 0) {
        this->touchPoints.emplace_back(x * 2.0 / this->screenWidth - 1.0);
        this->touchPoints.emplace_back(y * -2.0 / this->screenHeight + 1.0);
        this->touchIndices.emplace_back(this->index);
        this->numPoints = this->index + 1;
        this->index += 1;

        // Make arrays using vectors
        GLfloat *touches = &this->touchPoints[0];
        GLint *indices = &this->touchIndices[0];

        // Make the VAO active
        glBindVertexArray(this->VAO);

        // Make the VBO buffer active
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        // Copy the array containing vertices into VBO
        glBufferData(GL_ARRAY_BUFFER, this->touchPoints.size() * sizeof(GLfloat), touches, GL_STATIC_DRAW);

        // Make the EBO buffer active
        glBindBuffer(GL_ARRAY_BUFFER, this->EBO);
        // Copy the array containing indices into EBO
        glBufferData(GL_ARRAY_BUFFER, this->touchIndices.size() * sizeof(GLfloat), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        // Associate 0th attribute(defined in the vertex shader) with VBO
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        // Enable the 0th vertex attribute
        glEnableVertexAttribArray(0);

        // Add indices for indexed rendering, binding to GL_ELEMENT_ARRAY_BUFFER is saved with VAO state
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

        // Unbind the buffers and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Bind the shaders
        glUseProgram(this->shaderProgram);

        // Bind textureIn to texture unit 0
        GLint textureLocation = glGetUniformLocation(this->shaderProgram, "textureIn");
        glUniform1i(textureLocation, 0);

        // Activate the 0th texture unit
        glActiveTexture(GL_TEXTURE0);
        // Make the texture active
        glBindTexture(GL_TEXTURE_2D, this->simpleTextureID);

        glBindVertexArray(this->VAO);

        // Draw touch points
        glDrawElements(GL_POINTS, this->numPoints, GL_UNSIGNED_INT, nullptr);

        // Unbind
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);

    } else{
        glUseProgram(this->shaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->simpleTextureID);
        glBindVertexArray(this->VAO);
        glDrawElements(GL_POINTS, this->numPoints, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
    }
}

extern "C" {

void Java_com_example_openglplayground_GLRenderer_touchPointInit(JNIEnv *env, jclass obj) {
    touchPointObj.init();
}

void Java_com_example_openglplayground_GLRenderer_touchPointResize(JNIEnv *env, jclass obj, jint width, jint height) {
    touchPointObj.resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_touchPointRender(JNIEnv *env, jclass obj, jfloat x, jfloat y, jint isActionUp) {
    touchPointObj.render(x, y, isActionUp);
}

}

