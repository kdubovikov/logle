/* 
 * File:   BufferManager.cpp
 * Author: kdubovikov
 * 
 * Created on November 30, 2014, 5:45 PM
 */

#include "BufferManager.h"

template<class T>
GLuint BufferManager::addBuffer(const std::string& bufferName, std::vector<T>& bufferData) {
    GLuint bufferId = prepareBuffer(bufferData);
    bufferResourceManager.addResource(bufferName, bufferId);
    return bufferId;
}

GLuint BufferManager::getBufferId(const std::string& bufferName) {
    return bufferResourceManager.getResource(bufferName);
}


template <class T>
GLuint BufferManager::prepareBuffer(const std::vector<T>& bufferData) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(T), &bufferData[0], GL_STATIC_DRAW);
    
    return bufferId;
}

BufferManager::~BufferManager() {
    std::function<void (GLuint)> aciton = [](GLuint bufferId) { glDeleteBuffers(1, &bufferId); };
    bufferResourceManager.forEach(aciton);
}

template GLuint BufferManager::addBuffer<glm::vec2>(const std::string&, std::vector<glm::vec2>&);
template GLuint BufferManager::addBuffer<glm::vec3>(const std::string&, std::vector<glm::vec3>&);