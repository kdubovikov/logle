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
#include <string.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class Texture {
private:
    GLuint textureId;
public:
    bool load(const std::string &imagePath);
    bool customLoadDDS(const std::string &imagePath);
    void prepareTexture();
    GLuint getTextureId();
    ~Texture();
};

