/* 
 * File:   Camera.cpp
 * Author: kdubovikov
 * 
 * Created on November 1, 2014, 10:13 PM
 */

#include "Camera.h"

Camera::Camera() :
projectionMatrix(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)) {
}

void Camera::lookAt(glm::vec3& lookVector) {
    this->lookVector = lookVector;
}

void Camera::translate(glm::vec3& cameraPosition) {
    this->cameraPosition = cameraPosition;
}

void Camera::applyTransformation() {
    viewMatrix = glm::lookAt(cameraPosition, lookVector, glm::vec3(0, 1, 0));
}

glm::mat4& Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4& Camera::getProjectionMatrix() {
    return projectionMatrix;
}



