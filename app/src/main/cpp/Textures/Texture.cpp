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
        "in vec4 vPosition;\n"
        "in vec2 vTextureCord;\n"
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
        "uniform sampler2D textureIn;\n"
        "in vec2 textureCord;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "  fragColor = texture(textureIn, textureCord);\n"
        "}\n";

void Texture::init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Create the shader program
    this->shaderProgram = this->createShaderProgram(glVertexShader, glFragmentShader);
    // Create the texture and load it
    this->texture = loadSimpleTexture();
}

void Texture::resize(int width, int height){
    glViewport(0, 0, width, height);
    // Perspective projection
    this->projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));
    this->model = glm::mat4(1.0f);
}

GLuint Texture::loadShader(GLenum shaderType, const char *shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled){
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen){
            char *buf = (char *) malloc(infoLen);
            if (buf){
                glGetShaderInfoLog(shader, infoLen, nullptr, buf);
                LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                free(buf);
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

GLuint Texture::createShaderProgram(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShader = this->loadShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = this->loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE){
        GLint bufLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
        if (bufLength){
            char* buf = (char*) malloc(bufLength);
            if (buf){
                glGetProgramInfoLog(program, bufLength, nullptr, buf);
                LOGE("Could not link program:\n%s\n", buf);
                free(buf);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}

// Create a simple 3x3 texture
GLuint Texture::loadSimpleTexture(){
    // Texture object handle
    GLuint textureId;
    // 3x3 image, RGBA channels raw format
    GLubyte pixels[9 * 4] =
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
    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Generate a texture object
    glGenTextures(1, &textureId);
    // Activate the texture
    glActiveTexture(GL_TEXTURE0);
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);
    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}

void Texture::render(){
    // Create a vertex array object(VAO) and bind it
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a buffer object(VBO) for each attribute
    GLuint vbo[2];
    glGenBuffers(2, vbo);

    // Bind it to GL_ARRAY_BUFFER and pass the data to the GPU
    // for vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), &squareVertices, GL_STATIC_DRAW);
    // for texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), &textureCoordinates, GL_STATIC_DRAW);

    // Initialize the vertex vPosition and vTextureCord attributes defined in the vertex shader, get an index for the attribute from the shader
    GLuint positionLoc = glGetAttribLocation(this->shaderProgram, "vPosition");
    glEnableVertexAttribArray(positionLoc);
    GLuint textureCordLoc = glGetAttribLocation(this->shaderProgram, "vTextureCord");
    glEnableVertexAttribArray(textureCordLoc);

    // Associate the attribute with the data in the buffer.
    // glVertexAttribPointer implicitly refers to the currently bound GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(textureCordLoc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind the buffer and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind the shaders
    glUseProgram(this->shaderProgram);

    // Initialize the uniform matrices defined in the vertex shader
    int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(this->projection));
    int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
    int modelLoc = glGetUniformLocation(this->shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->model));

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, this->texture);

    // bind the VAO
    glBindVertexArray(vao);

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