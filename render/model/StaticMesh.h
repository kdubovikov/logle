/* 
 * File:   TextureGeometry.h
 * Author: kdubovikov
 *
 * Created on October 27, 2014, 4:33 PM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Texture.h"
#include "shader/CompilationResult.h"
#include "shader/ShaderManager.h"
#include "MeshLoader.h"
#include "lighting/LightSource.h"
#include "BufferManager.h"

class StaticMesh {
private:
    static const std::string MVP_UNIFORM_NAME;
    static const std::string VIEW_UNIFORM_NAME;
    static const std::string MODEL_UNIFORM_NAME;
    static const std::string SAMPLER_UNIFORM_NAME;
    static const std::string VERTEX_BUFFER_NAME;
    static const std::string UV_BUFFER_NAME;
    static const std::string NORMAL_BUFFER_NAME;
    
    ShaderManager shaderManager;
    Texture texture;
    BufferManager& bufferManager;
    
    std::vector<glm::vec3> verticies;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    size_t vertexBufferSize;
    GLuint vertexArrayId;

    glm::mat4 modelMatrix;
public:
    StaticMesh(Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager);
    StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager);
    void prepareShaders();
    void prepareTexture(const std::string &imagePath);
    void prepareDDSTextureCustom(const std::string &imagePath);
    void applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void render();
    void prepareLightSource(std::unique_ptr<LightSource>& light);
    ShaderManager& getShaderManager();
    glm::mat4& getModelMatrix();
    ~StaticMesh();
};
