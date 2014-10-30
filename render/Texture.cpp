/* 
 * File:   Texture.cpp
 * Author: kdubovikov
 * 
 * Created on October 30, 2014, 6:44 PM
 */

#include "Texture.h"

bool Texture::load(const std::string& imagePath) {
    textureId = SOIL_load_OGL_texture(imagePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    
    return textureId == 0;
}

void Texture::prepareTexture() {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint Texture::getTextureId() {
    return textureId;
}


Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

