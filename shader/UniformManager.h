/* 
 * File:   UniformManager.h
 * Author: kdubovikov
 *
 * Created on November 9, 2014, 2:45 AM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "core/ResourceManager.h"

class UniformManager {
private:
    GLuint shaderProgramId;
    ResourceManager<GLuint> uniformResourceManager;
    GLuint createUniform(const std::string& uniformName);
public:
    UniformManager(const GLuint shaderProgramId);
    GLuint getUniformId(const std::string& uniformName);
    void addMatrix4(const std::string& uniformName, const glm::mat4& matrix);
    void addVector3(const std::string& uniformName, const glm::vec3& vector);
    void addFloat(const std::string& uniformName, GLfloat number);
    void addSampler(const std::string& uniformName, GLint number);
};
