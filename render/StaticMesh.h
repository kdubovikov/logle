/* 
 * File:   TextureGeometry.h
 * Author: kdubovikov
 *
 * Created on October 27, 2014, 4:33 PM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include "glfw/glfw3.h
#include <glm/glm.hpp>

#include "Texture.h"
#include "CompilationResult.h"
#include "ShaderManager.h"
#include "MeshLoader.h"

class StaticMesh {
private:
    static const std::string MVP_UNIFORM_NAME;
    static const std::string VIEW_UNIFORM_NAME;
    static const std::string MODEL_UNIFORM_NAME;
    static const std::string SAMPLER_UNIFORM_NAME;
    
    ShaderManager shaderManager;
    Texture texture;
    
    std::vector<glm::vec3> verticies;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    size_t vertexBufferSize;
    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint normalBufferId;

    glm::mat4 modelMatrix;
    
    template <class T>
    GLuint prepareBuffer(const std::vector<T>& bufferData);
public:
    StaticMesh(Shader& vertexShader, Shader& fragmentShader);
    StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader);
    void prepareShaders();
    void prepareTexture(const std::string &imagePath);
    void prepareDDSTextureCustom(const std::string &imagePath);
    void prepareBuffers(const std::vector<glm::vec3>& vertexBufferData, const std::vector<glm::vec2>& uvBufferData, const std::vector<glm::vec3>& normalBufferData);
    void applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void render();
    ShaderManager& getShaderManager();
    glm::mat4& getModelMatrix();
    ~StaticMesh();
};
