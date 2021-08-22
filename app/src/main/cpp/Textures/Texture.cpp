#include "Textures.h"

Texture textureObj;

// Details of the square
const GLfloat squareVertices[] = {0.5, 0.5,
                                  0.5, -0.5,
                                  -0.5, -0.5,
                                  -0.5, 0.5};

const GLfloat textureCoordinates[] = {1.0, 1.0,  // Top right
                                      1.0, 0.0,  // Bottom right
                                      0.0, 0.0,  // Bottom left
                                      0.0, 1.0}; // Top left

// Vertex shader
static const char glVertexShader[] =
        "#version 310 es\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "layout (location = 0) in vec4 vPosition;\n"
        "layout (location = 1) in vec2 vTextureCord;\n"
        "out vec2 textureCord;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = projection * view * model * vPosition;\n"
        "  textureCord = vTextureCord;\n"
        "}\n";

// Fragment shader
static const char glFragmentShader[] =
        "#version 310 es\n"
        "precision mediump float;\n"
        "layout (binding = 0) uniform sampler2D textureIn;\n"
        "in vec2 textureCord;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "  fragColor = texture(textureIn, textureCord);\n"
        "}\n";

void Texture::init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Create a vertex array object(VAO)
    glGenVertexArrays(1, this->vao);
    // Create a buffer object(VBO) for each attribute
    glGenBuffers(2, this->vbo);

    // Create the shader program (loadShader & createShaderProgram functions are in Utils.cpp)
    this->shaderProgram = utils.createShaderProgram(glVertexShader, glFragmentShader);
    // Create the texture and load it
    this->simpleTextureID = this->createSimpleTexture();
}

void Texture::resize(int width, int height){
    glViewport(0, 0, width, height);
    // Perspective projection
    this->projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));
    this->model = glm::mat4(1.0f);
}

// Create a simple 3x3 texture
GLuint Texture::createSimpleTexture(){
    // Texture object handle
    GLuint textureId;
    // 3x3 image, RGBA channels raw format
    GLubyte data[9 * 4] =
        {
            18,  140, 171, 255, // Some color bottom left
            143, 143, 143, 255, // Some color bottom middle
            255, 255, 255, 255, // Some color bottom right
            255, 255, 0,   255, // Yellow middle left
            0,   255, 255, 255, // Some color middle
            255, 0,   255, 255, // Some color middle right
            255, 0,   0,   255, // Red top left
            0,   255, 0,   255, // Green top middle
            0,   0,   255, 255  // Blue top right
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

void Texture::render(){
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Make the vao active
    glBindVertexArray(this->vao[0]);

    // Make the 0th buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
    // Copy the array containing vertices into the 0th buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), &squareVertices, GL_STATIC_DRAW);

    // Make the 1st buffer active
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
    // Copy the array containing texture coordinates into the 1st buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), &textureCoordinates, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
    // Associate 0th attribute(defined in the vertex shader) with the 0th buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    // Enable the 0th vertex attribute
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
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

    // Activate the 0th texture unit
    glActiveTexture(GL_TEXTURE0);
    // Make the texture active
    glBindTexture(GL_TEXTURE_2D, this->simpleTextureID);

    glBindVertexArray(this->vao[0]);

    // Draw the square
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
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