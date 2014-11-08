#include "StaticMesh.h"

StaticMesh::StaticMesh(Shader& vertexShader, Shader& fragmentShader) :
shaderManager(ShaderManager()),
modelMatrix(glm::mat4(1.0f)) {
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
}

StaticMesh::StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader) {
    MeshLoader::load(modelPath, verticies, uvs, normals);
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
    prepareShaders();
    prepareBuffers(verticies, uvs);
}


void StaticMesh::prepareShaders() {
    // TODO: add some kind of AbstractResult class and return status
    CompilationResult shaderCompilationResult = shaderManager.compileShaders();

    if (shaderCompilationResult.status == CompilationResult::ERROR) {
        printf("Compile Error - %s \n", shaderCompilationResult.fileName.c_str());
        printf("Compile Error - %s \n", shaderCompilationResult.errorMessage.c_str());
        return;
    }

    shaderManager.link();
    
    int logLength;
    
    CompilationResult linkResult = shaderManager.checkResults();
    if (linkResult.status == CompilationResult::ERROR) {
        printf("Link Error - %s \n", linkResult.errorMessage.c_str());
        return;
    }
    
    textureUniformId = glGetUniformLocation(shaderManager.getShaderProgramId(), "textureSampler");
    mvpUniformId = glGetUniformLocation(shaderManager.getShaderProgramId(), "MVP");
}

void StaticMesh::prepareBuffers(const size_t vertexBufferSize, const std::vector<GLfloat>& vertexBufferData, const size_t uvBufferSize, const std::vector<GLfloat>& uvBufferData) {
    this->vertexBufferElemSize = vertexBufferSize;
    this->uvBufferElemSize = uvBufferSize;
    this->vertexBufferSize = vertexBufferData.size();
    
    vertexBufferId = prepareBuffer(vertexBufferData);
    uvBufferId = prepareBuffer(uvBufferData);
}

void StaticMesh::prepareBuffers(const std::vector<glm::vec3>& vertexBufferData, const std::vector<glm::vec2>& uvBufferData) {
    vertexBufferElemSize = 3;
    uvBufferElemSize = 2;
    vertexBufferSize = vertexBufferData.size() * vertexBufferElemSize;

    vertexBufferId = prepareBuffer(vertexBufferData);
    uvBufferId = prepareBuffer(uvBufferData);
}


void StaticMesh::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
}

void StaticMesh::prepareDDSTextureCustom(const std::string& imagePath) {
    texture.customLoadDDS(imagePath);
}


template <class T>
GLuint StaticMesh::prepareBuffer(const std::vector<T>& bufferData) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(T), &bufferData[0], GL_STATIC_DRAW);
    
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
    glVertexAttribPointer(0, vertexBufferElemSize, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    // TODO: abstract away buffer sizes, change from 3 to 2 breaks second tutorial
    glVertexAttribPointer(1, uvBufferElemSize, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glDrawArrays(GL_TRIANGLES, 0, vertexBufferSize / vertexBufferElemSize);
    
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