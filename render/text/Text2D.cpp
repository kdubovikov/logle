/* 
 * File:   Text2D.cpp
 * Author: kdubovikov
 * 
 * Created on November 30, 2014, 5:32 PM
 */

#include "Text2D.h"

const std::string Text2D::SAMPLER_UNIFORM_NAME = "fontSampler";

Text2D::Text2D(const std::string& fontTexturePath, size_t symbolSize, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager) :
Geometry(vertexShader, fragmentShader, bufferManager) {
    printf("Text constructor\n");
    this->symbolSize = symbolSize;
    fontTexture.load(fontTexturePath);
    fontTexture.prepareTexture();
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
}

void Text2D::print(const std::string& text, GLuint x, GLuint y) {
    for (std::string::size_type i = 0; i < text.size(); i++) {
        // count verticies
        glm::vec3 upLeft = glm::vec3(x + symbolSize * i, y + symbolSize, 0);
        glm::vec3 upRight = glm::vec3(upLeft.x + symbolSize, upLeft.y, 0);
        glm::vec3 downLeft = glm::vec3(upLeft.x, y, 0);
        glm::vec3 downRight = glm::vec3(upRight.x, y, 0);
        
        //first triangle of a quad
        verticies.push_back(upLeft);
        verticies.push_back(downLeft);
        verticies.push_back(upRight);
        
        //second triangle of a quad
        verticies.push_back(downRight);
        verticies.push_back(upRight);
        verticies.push_back(downLeft);
        
        char c = text[i];
        float uvX = (c % 16) / 16.0f;
        float uvY = (c / 16) / 16.0f;
        
        //count uvs
        glm::vec2 uvUpLeft = glm::vec2(uvX, uvY);
        glm::vec2 uvUpRight = glm::vec2(uvX + 1.0f / 16.0f, uvY);
        glm::vec2 uvDownLeft = glm::vec2(uvX, uvY + 1.0f / 16.0f);
        glm::vec2 uvDownRight = glm::vec2(uvUpRight.x, uvDownLeft.y);
        
        uvs.push_back(uvUpLeft);
        uvs.push_back(uvDownLeft);
        uvs.push_back(uvUpRight);
        
        uvs.push_back(uvDownRight);
        uvs.push_back(uvUpRight);
        uvs.push_back(uvDownLeft);
    }
    
    Geometry::prepareBuffers();
}

void Text2D::applyTransformation(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
}


void Text2D::preRender() {
    Geometry::preRender();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fontTexture.getTextureId());
    shaderManager.addUniform(SAMPLER_UNIFORM_NAME, 0);
}

void Text2D::postRender() {
    glDisable(GL_BLEND);
    Geometry::postRender();
}
