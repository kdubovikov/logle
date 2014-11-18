/* 
 * File:   StaticLight.h
 * Author: kdubovikov
 *
 * Created on November 10, 2014, 1:28 AM
 */

#pragma once
#include <glm/glm.hpp>

class StaticLight {
private:
    glm::vec3 position;
    glm::vec4 color;
public:
    glm::vec3& getPosition();
    void setPosition(glm::vec3& position);
    glm::vec4& getColor();
    void setColor(glm::vec4& color);
};

