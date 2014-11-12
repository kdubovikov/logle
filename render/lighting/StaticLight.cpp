/* 
 * File:   StaticLight.cpp
 * Author: kdubovikov
 * 
 * Created on November 10, 2014, 1:28 AM
 */

#include "StaticLight.h"

glm::vec4& StaticLight::getColor() {
    return color;
}

glm::vec3& StaticLight::getPosition() {
    return position;
}

void StaticLight::setColor(glm::vec4& color) {
    this->color = color;
}

void StaticLight::setPosition(glm::vec3& position) {
    this->position = position;
}





