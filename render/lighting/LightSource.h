/* 
 * File:   LightSource.h
 * Author: kdubovikov
 *
 * Created on November 19, 2014, 2:18 AM
 */

#pragma once

#define GL_GLEXT_PROTOTYPES
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include <string>

class LightSource {
private:
    glm::vec3 position;
    GLfloat power;
    glm::vec3 color;
public:
    static const std::string LIGHT_POSITION_UNIFORM_NAME;
    static const std::string LIGHT_POWER_UNIFORM_NAME;
    static const std::string LIGHT_COLOR_UNIFORM_NAME;
    
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3& position);
    
    glm::vec3 getColor() const;
    void setColor(glm::vec3& color);
    
    GLfloat getPower() const;
    void setPower(GLfloat power);
};