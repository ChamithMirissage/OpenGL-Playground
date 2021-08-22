#include "Polygons.h"

Polygons polygons;

// Vertex shader
static const char glVertexShader[] =
        "#version 310 es\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "layout (location = 0) in vec4 vPosition;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = projection * view * model * vPosition;\n"
        "}\n";

// Fragment shader
static const char glFragmentShader[] =
        "#version 310 es\n"
        "precision mediump float;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "  fragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
        "}\n";

void Polygons::init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Create a vertex array object(VAO)
    glGenVertexArrays(1, this->vao);
    // Create a buffer object(VBO) for each attribute
    glGenBuffers(1, this->vbo);

    // Create the shader program (loadShader & createShaderProgram functions are in Utils.cpp)
    this->shaderProgram = utils.createShaderProgram(glVertexShader, glFragmentShader);
}

void Polygons::resize(int width, int height) {
    glViewport(0, 0, width, height);
    // Perspective projection
    this->projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));
    this->model = glm::mat4(1.0f);
}

void Polygons::setLineVertices() {
    this->lineVertices[0] = -0.5;
    this->lineVertices[1] = -0.5;
    this->lineVertices[2] = 0.0;
    this->lineVertices[3] = 0.0;
    this->lineVertices[4] = 0.5;
    this->lineVertices[5] = 0.25;
}

void Polygons::setTriangleVertices() {
    this->triangleVertices[0] = 0.0;
    this->triangleVertices[1] = 0.5;
    this->triangleVertices[2] = -0.5;
    this->triangleVertices[3] = -0.5;
    this->triangleVertices[4] = 0.5;
    this->triangleVertices[5] = -0.5;
}

void Polygons::setSquareVertices() {
    this->squareVertices[0] = 0.5;
    this->squareVertices[1] = 0.5;
    this->squareVertices[2] = 0.5;
    this->squareVertices[3] = -0.5;
    this->squareVertices[4] = -0.5;
    this->squareVertices[5] = -0.5;
    this->squareVertices[6] = -0.5;
    this->squareVertices[7] = 0.5;
}

void Polygons::setHexagonVertices() {
    this->hexagonVertices[0] = -0.25;
    this->hexagonVertices[1] = 0.5;
    this->hexagonVertices[2] = -0.5;
    this->hexagonVertices[3] = 0.0;
    this->hexagonVertices[4] = -0.25;
    this->hexagonVertices[5] = -0.5;
    this->hexagonVertices[6] = 0.25;
    this->hexagonVertices[7] = -0.5;
    this->hexagonVertices[8] = 0.5;
    this->hexagonVertices[9] = 0.0;
    this->hexagonVertices[10] = 0.25;
    this->hexagonVertices[11] = 0.5;
}

void Polygons::setCircleVertices() {
    for (int i = 0; i < numVertices; i++){
        auto angle = i * 2.0 * PI / numVertices;
        this->circleVertices[2*i] = 0.5 * cos(angle);
        this->circleVertices[2*i + 1] = 0.5 * sin(angle);
    }
}

void Polygons::selectPolygon(int polyID) {
    switch (polyID) {
        case 0:
            this->numVertices = 3;
            this->setLineVertices();
            // Copy the array containing vertices into the 0th buffer
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->lineVertices), &this->lineVertices, GL_STATIC_DRAW);
            break;
        case 1:
            this->numVertices = 3;
            this->setTriangleVertices();
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->triangleVertices), &this->triangleVertices, GL_STATIC_DRAW);
            break;
        case 2:
            this->numVertices = 4;
            this->setSquareVertices();
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->squareVertices), &this->squareVertices, GL_STATIC_DRAW);
            break;
        case 3:
            this->numVertices = 6;
            this->setHexagonVertices();
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->hexagonVertices), &this->hexagonVertices, GL_STATIC_DRAW);
            break;
        case 4:
            this->numVertices = 100;
            this->setCircleVertices();
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->circleVertices), &this->circleVertices, GL_STATIC_DRAW);
            break;
    }
}

void Polygons::render() {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Make the vao active
    glBindVertexArray(this->vao[0]);

    // Make the 0th buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

    // Select the polygon to draw
    this->selectPolygon(this->polygonID);

    // Associate 0th attribute(defined in the vertex shader) with the 0th buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    // Enable the 0th vertex attribute
    glEnableVertexAttribArray(0);

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

    glBindVertexArray(this->vao[0]);

    // Draw the polygon
    if (this->polygonID == 0){
        glDrawArrays(GL_LINE_STRIP, 0, this->numVertices); // Line
    } else{
        glDrawArrays(GL_TRIANGLE_FAN, 0, this->numVertices); // Other polygons
    }

    // Unbind
    glBindVertexArray(0);
    glUseProgram(0);
}

extern "C" {

void Java_com_example_openglplayground_GLRenderer_polygonsInit(JNIEnv *env, jclass obj) {
    polygons.init();
}

void Java_com_example_openglplayground_GLRenderer_polygonsResize(JNIEnv *env, jclass obj, jint width, jint height) {
    polygons.resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_polygonsRender(JNIEnv *env, jclass obj) {
    polygons.render();
}

}



