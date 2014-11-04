/* 
 * File:   Camera.cpp
 * Author: kdubovikov
 * 
 * Created on November 1, 2014, 10:13 PM
 */

#include "Camera.h"

Camera::Camera() :
fov(45.0f),
projectionMatrix(glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)),
horizontalAngle(3.14f),
verticalAngle(0.0f) {
}

void Camera::lookAt(glm::vec3& lookVector) {
    this->lookVector = lookVector;
}

void Camera::applyTransformation() {
    viewMatrix = glm::lookAt(cameraPosition, cameraPosition + lookVector, upVector);
}

void Camera::computeVectors() {
    lookVector = glm::vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle));
    
    rightVector = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );
    
    upVector = glm::cross(rightVector, lookVector);
}

glm::mat4& Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4& Camera::getProjectionMatrix() {
    return projectionMatrix;
}

glm::vec3 Camera::getCameraPosition() const {
    return cameraPosition;
}

void Camera::setCameraPosition(glm::vec3& cameraPosition) {
    this->cameraPosition = cameraPosition;
}

float Camera::getFov() const {
    return fov;
}

void Camera::setFov(float fov) {
    this->fov = fov;
}

float Camera::getHorizontalAngle() const {
    return horizontalAngle;
}

void Camera::substractFromHorizontalAngle(float horizontalAngle) {
    this->horizontalAngle -= horizontalAngle;
}

float Camera::getVerticalAngle() const {
    return verticalAngle;
}

void Camera::addToVerticalAngle(float verticalAngle) {
    this->verticalAngle += verticalAngle;
}

glm::vec3 Camera::getLookVector() const {
    return lookVector;
}

glm::vec3 Camera::getUpVector() const {
    return upVector;
}

glm::vec3 Camera::getRightVector() const {
    return rightVector;
}

