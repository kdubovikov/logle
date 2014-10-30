/* 
 * File:   Texture.h
 * Author: kdubovikov
 *
 * Created on October 30, 2014, 6:44 PM
 */

#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include "../soil2/SOIL2.h"
#include <string>

class Texture {
private:
    GLuint textureId;
public:
    bool load(const std::string &imagePath);
    void prepareTexture();
    GLuint getTextureId();
    ~Texture();
};

