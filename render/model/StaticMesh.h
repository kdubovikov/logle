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
#include "shader/CompilationResult.h"
#include "shader/ShaderManager.h"
#include "MeshLoader.h"
#include "lighting/LightSource.h"
#include "BufferManager.h"
#include "geometry/Geometry.h"

class StaticMesh : public Geometry {
private:
    static const std::string SAMPLER_UNIFORM_NAME;    
    Texture texture;
public:
    StaticMesh(const std::string& modelPath, Shader& vertexShader, Shader& fragmentShader, BufferManager& bufferManager);
    void prepareTexture(const std::string &imagePath);
    void prepareDDSTextureCustom(const std::string &imagePath);
    void prepareLightSource(std::unique_ptr<LightSource>& light);
    virtual void preRender();
};
