#include "StaticMesh.h"

const std::string StaticMesh::MVP_UNIFORM_NAME = "MVP";
const std::string StaticMesh::VIEW_UNIFORM_NAME = "V";
const std::string StaticMesh::MODEL_UNIFORM_NAME = "M";
const std::string StaticMesh::SAMPLER_UNIFORM_NAME = "textureSampler";
const std::string StaticMesh::VERTEX_BUFFER_NAME = "vertexBuffer";
const std::string StaticMesh::UV_BUFFER_NAME = "uvBuffer";
const std::string StaticMesh::NORMAL_BUFFER_NAME = "normalBuffer";

StaticMesh::StaticMesh(Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager) :
shaderManager(),
modelMatrix(glm::mat4(1.0f)),
bufferManager(bufferManager) {
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
}

StaticMesh::StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager) : 
bufferManager(bufferManager) {
    MeshLoader::load(modelPath, verticies, uvs, normals);
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
    prepareShaders();
    
    vertexBufferSize = verticies.size() * 3;
    bufferManager.addBuffer(VERTEX_BUFFER_NAME, verticies);
    bufferManager.addBuffer(UV_BUFFER_NAME, uvs);
    bufferManager.addBuffer(NORMAL_BUFFER_NAME, normals);
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

void StaticMesh::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
}

void StaticMesh::prepareDDSTextureCustom(const std::string& imagePath) {
    texture.customLoadDDS(imagePath);
}

void StaticMesh::applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    shaderManager.addUniform(MVP_UNIFORM_NAME, mvp);
    shaderManager.addUniform(VIEW_UNIFORM_NAME, viewMatrix);
    shaderManager.addUniform(MODEL_UNIFORM_NAME, modelMatrix);
    
    GLuint LightID = glGetUniformLocation(shaderManager.getShaderProgramId(), "LightPosition_worldspace");
    glm::vec3 lightPos = glm::vec3(4,4,4);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
}

void StaticMesh::render() {
    glUseProgram(shaderManager.getShaderProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(shaderManager.getUniformId(SAMPLER_UNIFORM_NAME), 0);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(VERTEX_BUFFER_NAME));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(UV_BUFFER_NAME));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(NORMAL_BUFFER_NAME));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
    glDrawArrays(GL_TRIANGLES, 0, vertexBufferSize / 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void StaticMesh::prepareLightSource(std::unique_ptr<LightSource>& light) {
    shaderManager.addUniform(light.get()->LIGHT_COLOR_UNIFORM_NAME, light.get()->getColor());
    shaderManager.addUniform(light.get()->LIGHT_POSITION_UNIFORM_NAME, light.get()->getPosition());
    shaderManager.addUniform(light.get()->LIGHT_POWER_UNIFORM_NAME, light.get()->getPower());
}

ShaderManager& StaticMesh::getShaderManager() {
    return shaderManager;
}

glm::mat4& StaticMesh::getModelMatrix() {
    return modelMatrix;
}

StaticMesh::~StaticMesh() {
    glDeleteVertexArrays(1, &vertexArrayId);
}