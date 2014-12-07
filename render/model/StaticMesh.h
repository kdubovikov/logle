/* 
 * File:   TextureGeometry.h
 * Author: kdubovikov
 *
 * Created on October 27, 2014, 4:33 PM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Texture.h"
#include "MeshLoader.h"
#include "lighting/LightSource.h"
#include "geometry/Geometry.h"

class StaticMesh : public Geometry {
private:
    static const std::string SAMPLER_UNIFORM_NAME; 
    static const std::string NORMAL_BUFFER_NAME; 
    
    Texture texture;
    virtual void prepareBuffers();
    virtual void preRender();
    virtual void postRender();
    
public:
    StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager);
    void prepareTexture(const std::string &imagePath);
    void prepareDDSTextureCustom(const std::string &imagePath);
    void prepareLightSource(std::unique_ptr<LightSource>& light);
    void loadModel(const std::string& modelPath);
};
