#include "StaticMesh.h"

const std::string StaticMesh::SAMPLER_UNIFORM_NAME = "textureSampler";
const std::string StaticMesh::NORMAL_BUFFER_NAME = "normalBuffer";

StaticMesh::StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager) : 
 Geometry::Geometry(vertexShader, fragmentShader, bufferManager) {
    loadModel(modelPath);
}

void StaticMesh::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
}

void StaticMesh::prepareDDSTextureCustom(const std::string& imagePath) {
    texture.customLoadDDS(imagePath);
}

void StaticMesh::prepareBuffers() {
    bufferManager.addBuffer(VERTEX_BUFFER_NAME, verticies);
    bufferManager.addBuffer(UV_BUFFER_NAME, uvs);
    bufferManager.addBuffer(NORMAL_BUFFER_NAME, normals);
}

void StaticMesh::loadModel(const std::string& modelPath) {
    MeshLoader::load(modelPath, verticies, uvs, normals);
    prepareBuffers();
}


void StaticMesh::preRender() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(shaderManager.getUniformId(SAMPLER_UNIFORM_NAME), 0);
    
    Geometry::preRender();
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(NORMAL_BUFFER_NAME));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

void StaticMesh::postRender() {
    Geometry::postRender();
    glDisableVertexAttribArray(2);
}

void StaticMesh::prepareLightSource(std::unique_ptr<LightSource>& light) {
    shaderManager.addUniform(light.get()->LIGHT_COLOR_UNIFORM_NAME, light.get()->getColor());
    shaderManager.addUniform(light.get()->LIGHT_POSITION_UNIFORM_NAME, light.get()->getPosition());
    shaderManager.addUniform(light.get()->LIGHT_POWER_UNIFORM_NAME, light.get()->getPower());
}