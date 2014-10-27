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

class SimpleGeometry {
private:  
    GLuint vertexBufferId;
    GLuint colorBufferId;
    size_t bufferSize;
    ShaderManager shaderManager;
    Shader vertexShader;
    Shader fragmentShader;
    
    GLuint prepareBuffer(const GLfloat* bufferData);
public:
    SimpleGeometry(size_t bufferSize, const GLfloat* vertexBufferData, const GLfloat* colorBufferData, std::string vertexShaderPath, std::string fragmentShaderPath);
    void prepareShaders();
    void render();
    ShaderManager getShaderManager();
    ~SimpleGeometry();
};
