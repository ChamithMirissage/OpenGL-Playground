#include "Shader.h"

Shader shaderObj;

void Shader::init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Create a vertex array object(VAO)
    glGenVertexArrays(1, &this->vao);
    // Create a buffer object(VBO) for each attribute
    glGenBuffers(2, this->vbo);

    // Create the shader program (loadShader & createShaderProgram functions are in ShaderUtils.cpp)
    this->shaderProgram = ShaderUtils::createShaderProgram(this->glVertexShader, this->glFragmentShader);
}

void Shader::resize(int width, int height) {
    glViewport(0, 0, width, height);
    // Perspective projection
    this->projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));
    this->model = glm::mat4(1.0f);
}

void Shader::render() {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Make the vao active
    glBindVertexArray(this->vao);

    // Make the 0th buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
    // Copy the array containing vertices into the 0th buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), &squareVertices, GL_STATIC_DRAW);

    // Make the 1st buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
    // Copy the array containing colors into the 1st buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexColors), &squareVertexColors, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
    // Associate 0th attribute(defined in the vertex shader) with the 0th buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    // Enable the 0th vertex attribute
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    // Unbind the buffer and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bind the shaders
    glUseProgram(this->shaderProgram);

    // Initialize the uniform matrices defined in the vertex shader
    int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(this->projection));
    int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
    int modelLoc = glGetUniformLocation(this->shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->model));

    glBindVertexArray(this->vao);

    // Draw the square
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind
    glBindVertexArray(0);
    glUseProgram(0);
}

extern "C" {

void Java_com_example_openglplayground_GLRenderer_shaderInit(JNIEnv *env, jclass obj) {
    shaderObj.init();
}

void Java_com_example_openglplayground_GLRenderer_shaderResize(JNIEnv *env, jclass obj, jint width, jint height) {
    shaderObj.resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_shaderRender(JNIEnv *env, jclass obj) {
    shaderObj.render();
}

}

