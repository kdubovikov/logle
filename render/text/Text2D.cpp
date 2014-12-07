/* 
 * File:   Text2D.cpp
 * Author: kdubovikov
 * 
 * Created on November 30, 2014, 5:32 PM
 */

#include "Text2D.h"

const std::string Text2D::VERTEX_BUFFER_NAME = "vertexBuffer";
const std::string Text2D::UV_BUFFER_NAME = "uvBuffer";
const std::string Text2D::SAMPLER_UNIFORM_NAME = "fontSampler";

void Text2D::prepareFont(const std::string& fontTexturePath, Shader& vertexShader, Shader& fragmentShader, size_t symbolSize) {
    this->symbolSize = symbolSize;
    fontTexture.customLoadDDS(fontTexturePath);
    
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
    //TODO: incapsulate prepareShaders from StaticMesh into ShaderManager and use it
    shaderManager.compileShaders();
    shaderManager.link();
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
}

void Text2D::print(const std::string& text, GLuint x, GLuint y) {
    for (std::string::size_type i = 0; i < text.size(); i++) {
        // count verticies
        glm::vec2 upLeft = glm::vec2(x + symbolSize * i, y + symbolSize);
        glm::vec2 upRight = glm::vec2(upLeft.x + symbolSize, upLeft.y);
        glm::vec2 downLeft = glm::vec2(upLeft.x, y);
        glm::vec2 downRight = glm::vec2(upRight.x, y);
        
        //first triangle of a quad
        vertexList.push_back(upLeft);
        vertexList.push_back(downLeft);
        vertexList.push_back(upRight);
        
        //second triangle of a quad
        vertexList.push_back(downRight);
        vertexList.push_back(upRight);
        vertexList.push_back(downLeft);
        
        char c = text[i];
        float uvX = (c % 16) / 16.0f;
        float uvY = (c / 16) / 16.0f;
        
        //count uvs
        upLeft = glm::vec2(uvX, uvY);
        upRight = glm::vec2(upLeft.x + 1.0f / 16.0f, uvY);
        downLeft = glm::vec2(uvX, uvY + 1.0f / 16.0f);
        downRight = glm::vec2(upRight.x, downLeft.y);
        
        uvList.push_back(upLeft);
        uvList.push_back(downLeft);
        uvList.push_back(upRight);
        
        uvList.push_back(downRight);
        uvList.push_back(upRight);
        uvList.push_back(downLeft);
    }
    
    bufferManager.addBuffer(VERTEX_BUFFER_NAME, vertexList);
    bufferManager.addBuffer(UV_BUFFER_NAME, uvList);
}

void Text2D::render() {
    // TODO: incapsulate this login using lambdas
    glUseProgram(shaderManager.getShaderProgramId());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fontTexture.getTextureId());
    glUniform1i(shaderManager.getUniformId(SAMPLER_UNIFORM_NAME), 0);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(VERTEX_BUFFER_NAME));
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, bufferManager.getBufferId(UV_BUFFER_NAME));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_TRIANGLES, 0, vertexList.size() / 3);
    
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
