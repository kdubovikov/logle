/* 
 * File:   TextureGeometry.h
 * Author: kdubovikov
 *
 * Created on October 27, 2014, 4:33 PM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "CompilationResult.h"
#include "ShaderManager.h"

class StaticMesh {
private:  
    size_t bufferSize;
    ShaderManager shaderManager;
    Texture texture;
    
    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint textureUniformId;
    GLuint mvpUniformId;
    
    glm::mat4 modelMatrix;

    GLuint prepareBuffer(const std::vector<GLfloat>& bufferData);
public:
    StaticMesh(const size_t bufferSize, Shader& vertexShader, Shader& fragmentShader);
    void prepareShaders();
    void prepareTexture(const std::string &imagePath);
    void prepareBuffers(const std::vector<GLfloat>& vertexBufferData, const std::vector<GLfloat>& uvBufferData);
    void applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void render();
    ShaderManager& getShaderManager();
    glm::mat4& getModelMatrix();
    ~StaticMesh();
};
