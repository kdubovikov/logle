/* 
 * File:   TextureGeometry.h
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

class TexturedGeometry {
private:  
    size_t bufferSize;
    ShaderManager shaderManager;
    Texture texture;
    
    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint textureUniformId;

    GLuint prepareBuffer(const std::vector<GLfloat>& bufferData);
public:
    TexturedGeometry(const size_t bufferSize, Shader& vertexShader, Shader& fragmentShader);
    void prepareShaders();
    void prepareTexture(const std::string &imagePath);
    void prepareBuffers(const std::vector<GLfloat>& vertexBufferData, const std::vector<GLfloat>& uvBufferData);
    void render();
    ShaderManager& getShaderManager();
    ~TexturedGeometry();
};
