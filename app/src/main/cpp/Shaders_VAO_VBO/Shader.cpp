#include <jni.h>
#include <android/log.h>

#include <GLES3/gl31.h>

#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#define  LOG_TAG    "Shader"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


glm::mat4 projection;
glm::mat4 model;
glm::mat4 view;

// Details of the square
const GLfloat squareVertices[] = {0.5, 0.5,
                                  0.5, -0.5,
                                  -0.5, -0.5,
                                  -0.5, 0.5};
const GLfloat squareVertexColors[] = {1.0, 0.0, 0.0,
                                      0.0, 1.0, 0.0,
                                      0.0, 0.0, 1.0,
                                      1.0, 1.0, 0.0};

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);
    // Perspective projection
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    model = glm::mat4(1.0f);
}

// Vertex shader
static const char glVertexShader[] =
        "#version 310 es\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "in vec4 vPosition;\n"
        "in vec4 vColor;\n"
        "out vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = projection * view * model * vPosition;\n"
        "  vertexColor = vColor;\n"
        "}\n";

// Fragment shader
static const char glFragmentShader[] =
        "#version 310 es\n"
        "precision mediump float;\n"
        "in vec4 vertexColor;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "  fragColor = vertexColor;\n"
        "}\n";

GLuint loadShader(GLenum shaderType, const char *shaderSource) {
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

GLuint createShaderProgram(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
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

void render() {
    // Create the shader program
    GLuint shaderProgram = createShaderProgram(glVertexShader, glFragmentShader);

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
    // for colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexColors), &squareVertexColors, GL_STATIC_DRAW);

    // Initialize the vertex vPosition and vColor attributes defined in the vertex shader, get an index for the attribute from the shader
    GLuint positionLoc = glGetAttribLocation(shaderProgram, "vPosition");
    glEnableVertexAttribArray(positionLoc);
    GLuint colorLoc = glGetAttribLocation(shaderProgram, "vColor");
    glEnableVertexAttribArray(colorLoc);

    // Associate the attribute with the data in the buffer.
    // glVertexAttribPointer implicitly refers to the currently bound GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind the buffer and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bind the shaders
    glUseProgram(shaderProgram);

    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Initialize the uniform matrices defined in the vertex shader
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // bind the VAO
    glBindVertexArray(vao);

    // Draw the square
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind
    glUseProgram(0);
    glBindVertexArray(0);
}

extern "C" {

void Java_com_example_openglplayground_GLRenderer_shaderInit(JNIEnv *env, jclass obj) {
    init();
}

void Java_com_example_openglplayground_GLRenderer_shaderResize(JNIEnv *env, jclass obj, jint width, jint height) {
    resize(width, height);
}

void Java_com_example_openglplayground_GLRenderer_shaderRender(JNIEnv *env, jclass obj) {
    render();
}

}

