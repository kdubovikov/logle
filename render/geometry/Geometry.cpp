/* 
 * File:   Geometry.cpp
 * Author: kdubovikov
 * 
 * Created on December 7, 2014, 3:39 PM
 */

#include "Geometry.h"

const std::string Geometry::MVP_UNIFORM_NAME = "MVP";
const std::string Geometry::VIEW_UNIFORM_NAME = "V";
const std::string Geometry::MODEL_UNIFORM_NAME = "M";
const std::string Geometry::VERTEX_BUFFER_NAME = "vertexBuffer";
const std::string Geometry::UV_BUFFER_NAME = "uvBuffer";
const std::string Geometry::NORMAL_BUFFER_NAME = "normalBuffer";

Geometry::Geometry(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager) :
bufferManager(bufferManager) {
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    MeshLoader::load(modelPath, verticies, uvs, normals);
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
    prepareShaders();
    
    vertexBufferSize = verticies.size() * 3;
    bufferManager.addBuffer(VERTEX_BUFFER_NAME, verticies);
    bufferManager.addBuffer(UV_BUFFER_NAME, uvs);
    bufferManager.addBuffer(NORMAL_BUFFER_NAME, normals);
}

void Geometry::prepareShaders() {
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


void Geometry::applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    shaderManager.addUniform(MVP_UNIFORM_NAME, mvp);
    shaderManager.addUniform(VIEW_UNIFORM_NAME, viewMatrix);
    shaderManager.addUniform(MODEL_UNIFORM_NAME, modelMatrix);
}

void Geometry::preRender() {
    glUseProgram(shaderManager.getShaderProgramId());
   
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(VERTEX_BUFFER_NAME));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(UV_BUFFER_NAME));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(NORMAL_BUFFER_NAME));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

void Geometry::render() {    
    preRender();
    glDrawArrays(GL_TRIANGLES, 0, vertexBufferSize / 3);
    postRender();
}

void Geometry::postRender() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

glm::mat4& Geometry::getModelMatrix() {
    return modelMatrix;
}

ShaderManager& Geometry::getShaderManager() {
    return shaderManager;
}

Geometry::~Geometry() {
    glDeleteVertexArrays(1, &vertexArrayId);
}






