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
#include "MeshLoader.h"

class StaticMesh {
private:  
    size_t vertexBufferElemSize;
    size_t uvBufferElemSize;
    size_t vertexBufferSize;
    ShaderManager shaderManager;
    Texture texture;
    
    std::vector<glm::vec3> verticies;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint textureUniformId;
    GLuint mvpUniformId;
    
    glm::mat4 modelMatrix;
    
    template <class T>
    GLuint prepareBuffer(const std::vector<T>& bufferData);
public:
    StaticMesh(Shader& vertexShader, Shader& fragmentShader);
    StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader);
    void prepareShaders();
    void prepareTexture(const std::string &imagePath);
    void prepareBuffers(const size_t vertexBufferSize, const std::vector<GLfloat>& vertexBufferData, const size_t uvBufferSize, const std::vector<GLfloat>& uvBufferData);
    void prepareBuffers(const std::vector<glm::vec3>& vertexBufferData, const std::vector<glm::vec2>& uvBufferData);
    void applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void render();
    ShaderManager& getShaderManager();
    glm::mat4& getModelMatrix();
    ~StaticMesh();
};
