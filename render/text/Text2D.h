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
#include "geometry/Geometry.h"

class Text2D : public Geometry {
private:
    Texture fontTexture;
    size_t symbolSize;
    
    static const std::string SAMPLER_UNIFORM_NAME;

    virtual void preRender();
    virtual void postRender();
    virtual void applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
public:
    Text2D(const std::string& fontTexturePath, size_t symbolSize, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager);
    void print(const std::string& text, GLuint x, GLuint y);
};