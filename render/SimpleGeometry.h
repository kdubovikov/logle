/* 
 * File:   simple_geometry.h
 * Author: kdubovikov
 *
 * Created on October 27, 2014, 4:33 PM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <functional>

#include "ShaderManager.h"
#include "Texture.h"

class SimpleGeometry {
private:  
    size_t bufferSize;
    ShaderManager shaderManager;
    GLuint vertexBufferId;
    GLuint colorBufferId;

    GLuint prepareBuffer(const std::vector<GLfloat>& bufferData);
public:
    SimpleGeometry(const size_t bufferSize, Shader& vertexShader, Shader& fragmentShader);
    void prepareShaders();
    void prepareBuffers(const std::vector<GLfloat>& vertexBufferData, const std::vector<GLfloat>& colorBufferData);
    void render();
    ShaderManager& getShaderManager();
    ~SimpleGeometry();
};
