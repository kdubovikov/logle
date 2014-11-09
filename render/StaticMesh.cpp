#include "StaticMesh.h"

const std::string StaticMesh::MVP_UNIFORM_NAME = "MVP";
const std::string StaticMesh::VIEW_UNIFORM_NAME = "V";
const std::string StaticMesh::MODEL_UNIFORM_NAME = "M";
const std::string StaticMesh::SAMPLER_UNIFORM_NAME = "textureSampler";

StaticMesh::StaticMesh(Shader& vertexShader, Shader& fragmentShader) :
shaderManager(),
modelMatrix(glm::mat4(1.0f)) {
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
}

StaticMesh::StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader) {
    MeshLoader::load(modelPath, verticies, uvs, normals);
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
    prepareShaders();
    prepareBuffers(verticies, uvs, normals);
}


void StaticMesh::prepareShaders() {
    // TODO: add some kind of AbstractResult class and return status
    CompilationResult shaderCompilationResult = shaderManager.compileShaders();

    if (shaderCompilationResult.status == CompilationResult::ERROR) {
        printf("Compile Error - %s \n", shaderCompilationResult.fileName.c_str());
        printf("Compile Error - %s \n", shaderCompilationResult.errorMessage.c_str());
        return;
    }

    CompilationResult linkResult = shaderManager.link();
    
    if (linkResult.status == CompilationResult::ERROR) {
        printf("Link Error - %s \n", linkResult.errorMessage.c_str());
        return;
    }    
}

void StaticMesh::prepareBuffers(const std::vector<glm::vec3>& vertexBufferData, const std::vector<glm::vec2>& uvBufferData, const std::vector<glm::vec3>& normalBufferData) {
    vertexBufferSize = vertexBufferData.size() * 3;

    vertexBufferId = prepareBuffer(vertexBufferData);
    uvBufferId = prepareBuffer(uvBufferData);
    normalBufferId = prepareBuffer(normalBufferData);
}


void StaticMesh::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
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
    shaderManager.addUniform(MVP_UNIFORM_NAME, mvp);
    
}

void StaticMesh::render() {
    glUseProgram(shaderManager.getShaderProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(shaderManager.getUniformId(SAMPLER_UNIFORM_NAME), 0);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    // Simple back compability check
    if (normalBufferId != 0) {
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, vertexBufferSize / 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    // Simple back compability check
    if (normalBufferId != 0) {
        glDisableVertexAttribArray(2);
    }
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
    glDeleteBuffers(1, &normalBufferId);
}