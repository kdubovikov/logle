/* 
 * File:   BufferManager.h
 * Author: kdubovikov
 *
 * Created on November 30, 2014, 5:45 PM
 */
#pragma once
#define GL_GLEXT_PROTOTYPES
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "core/ResourceManager.h"
#include <vector>
#include <unordered_map>

class BufferManager {
private:
    ResourceManager<GLuint> bufferResourceManager;    
    
    template <class T>
    GLuint prepareBuffer(const std::vector<T>& bufferData);
public:
    template<class T>
    GLuint addBuffer(const std::string& bufferName, std::vector<T>& bufferData);
    
    GLuint getBufferId(const std::string& bufferName);
    ~BufferManager();
};

