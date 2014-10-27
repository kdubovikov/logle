#include "SimpleGeometry.h"

SimpleGeometry::SimpleGeometry(size_t bufferSize, const GLfloat* vertexBufferData, const GLfloat* colorBufferData, std::string vertexShaderPath, std::string fragmentShaderPath) :
shaderManager(ShaderManager()),
bufferSize(bufferSize),
vertexShader(Shader(vertexShaderPath, GL_VERTEX_SHADER)),
fragmentShader(Shader(fragmentShaderPath, GL_FRAGMENT_SHADER)) {
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
    vertexBufferId = prepareBuffer(vertexBufferData);
    colorBufferId = prepareBuffer(colorBufferData);
}

void SimpleGeometry::prepareShaders() {
    // TODO: add some kind of AbstractResult class and return status
    CompilationResult shaderCompilationResult = shaderManager.compileShaders();

    if (shaderCompilationResult.status == CompilationResult::ERROR) {
        printf("%s \n", shaderCompilationResult.fileName.c_str());
        printf("%s \n", shaderCompilationResult.errorMessage.c_str());
        return;
    }

    shaderManager.link();

    CompilationResult linkResult = shaderManager.checkResults();
    if (linkResult.status == CompilationResult::ERROR) {
        printf("%s \n", linkResult.errorMessage.c_str());
        return;
    }
}

void SimpleGeometry::render() {
    glUseProgram(shaderManager.getShaderProgramId());

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_TRIANGLES, 0, bufferSize * 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

GLuint SimpleGeometry::prepareBuffer(const GLfloat* bufferData) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), &bufferData, GL_STATIC_DRAW);

    return bufferId;
}

ShaderManager SimpleGeometry::getShaderManager() {
    return shaderManager;
}

SimpleGeometry::~SimpleGeometry() {
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &colorBufferId);
}