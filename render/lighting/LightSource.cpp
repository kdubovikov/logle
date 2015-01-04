/* 
 * File:   LightSource.cpp
 * Author: kdubovikov
 * 
 * Created on November 19, 2014, 2:18 AM
 */

#include "LightSource.h"

const std::string LightSource::LIGHT_COLOR_UNIFORM_NAME = "LightColor";
const std::string LightSource::LIGHT_POSITION_UNIFORM_NAME = "LightPosition";
const std::string LightSource::LIGHT_POWER_UNIFORM_NAME = "LightPower";

glm::vec3 LightSource::getColor() const {
    return color;
}

void LightSource::setColor(glm::vec3& color) {
    this->color = color;
}

glm::vec3 LightSource::getPosition() const {
    return position;
}

void LightSource::setPosition(glm::vec3& position) {
    this->position = position;
}

GLfloat LightSource::getPower() const {
    return power;
}

void LightSource::setPower(GLfloat power) {
    this->power = power;
}





