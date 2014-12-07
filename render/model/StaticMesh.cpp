#include "StaticMesh.h"

const std::string StaticMesh::SAMPLER_UNIFORM_NAME = "textureSampler";

StaticMesh::StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager) : 
 Geometry::Geometry(modelPath, vertexShader, fragmentShader, bufferManager) {
}

void StaticMesh::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
}

void StaticMesh::prepareDDSTextureCustom(const std::string& imagePath) {
    texture.customLoadDDS(imagePath);
}

void StaticMesh::preRender() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(shaderManager.getUniformId(SAMPLER_UNIFORM_NAME), 0);
    
    Geometry::preRender();
}


void StaticMesh::prepareLightSource(std::unique_ptr<LightSource>& light) {
    //GLuint LightID = glGetUniformLocation(shaderManager.getShaderProgramId(), "LightPosition_worldspace");
    //glm::vec3 lightPos = glm::vec3(4,4,4);
    //glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
    
    shaderManager.addUniform(light.get()->LIGHT_COLOR_UNIFORM_NAME, light.get()->getColor());
    shaderManager.addUniform(light.get()->LIGHT_POSITION_UNIFORM_NAME, light.get()->getPosition());
    shaderManager.addUniform(light.get()->LIGHT_POWER_UNIFORM_NAME, light.get()->getPower());
}