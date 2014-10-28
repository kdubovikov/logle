#include "SimpleGeometry.h"

SimpleGeometry::SimpleGeometry(size_t bufferSize, Shader& vertexShader, Shader& fragmentShader) :
shaderManager(ShaderManager()),
bufferSize(bufferSize) {
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
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

void SimpleGeometry::prepareBuffers(std::vector<GLfloat>& vertexBufferData, std::vector<GLfloat>& colorBufferData) {
    vertexBufferId = prepareBuffer(vertexBufferData);
    colorBufferId = prepareBuffer(colorBufferData);
}

GLuint SimpleGeometry::prepareBuffer(std::vector<GLfloat>& bufferData) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(GLfloat), bufferData.data(), GL_STATIC_DRAW);
    
    return bufferId;
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

ShaderManager& SimpleGeometry::getShaderManager() {
    return shaderManager;
}

SimpleGeometry::~SimpleGeometry() {
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &colorBufferId);
}