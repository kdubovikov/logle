/* 
 * File:   Text2D.h
 * Author: kdubovikov
 *
 * Created on November 30, 2014, 5:32 PM
 */
#pragma once
#define GL_GLEXT_PROTOTYPES
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Texture.h"
#include "shader/ShaderManager.h"
#include "shader/Shader.h"
#include "BufferManager.h"

class Text2D {
private:
    Texture fontTexture;
    size_t symbolSize;
    
    std::vector<glm::vec2> vertexList;
    std::vector<glm::vec2> uvList;
    
    ShaderManager shaderManager;
    BufferManager bufferManager;
    
    static const std::string VERTEX_BUFFER_NAME;
    static const std::string UV_BUFFER_NAME;
    static const std::string SAMPLER_UNIFORM_NAME;
public:
    void prepareFont(const std::string& fontTexturePath, Shader& vertexShader, Shader& fragmentShader, size_t symbolSize);
    void print(const std::string& text, GLuint x, GLuint y);
    void render();
};