#include "StaticMesh.h"

StaticMesh::StaticMesh(const size_t bufferSize, Shader& vertexShader, Shader& fragmentShader) :
shaderManager(ShaderManager()),
bufferSize(bufferSize),
modelMatrix(glm::mat4(1.0f)) {
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
}

void StaticMesh::prepareShaders() {
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
    
    textureUniformId = glGetUniformLocation(shaderManager.getShaderProgramId(), "textureSampler");
    mvpUniformId = glGetUniformLocation(shaderManager.getShaderProgramId(), "MVP");
}

void StaticMesh::prepareBuffers(const std::vector<GLfloat>& vertexBufferData, const std::vector<GLfloat>& uvBufferData) {
    vertexBufferId = prepareBuffer(vertexBufferData);
    uvBufferId = prepareBuffer(uvBufferData);
}

void StaticMesh::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
}

GLuint StaticMesh::prepareBuffer(const std::vector<GLfloat>& bufferData) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(GLfloat), bufferData.data(), GL_STATIC_DRAW);
    
    return bufferId;
}

void StaticMesh::applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(mvpUniformId, 1, GL_FALSE, &mvp[0][0]);
}

void StaticMesh::render() {
    glUseProgram(shaderManager.getShaderProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(textureUniformId, 0);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    // TODO: abstract away buffer sizes, change from 3 to 2 breaks second tutorial
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_TRIANGLES, 0, bufferSize * 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

ShaderManager& StaticMesh::getShaderManager() {
    return shaderManager;
}

glm::mat4& StaticMesh::getModelMatrix() {
    return modelMatrix;
}

StaticMesh::~StaticMesh() {
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &uvBufferId);
}