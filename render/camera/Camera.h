/* 
 * File:   Camera.h
 * Author: kdubovikov
 *
 * Created on November 1, 2014, 10:13 PM
 */
#pragma once
#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class Camera {
private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 cameraPosition;
    glm::vec3 lookVector;
    glm::vec3 upVector;
    glm::vec3 rightVector;
    
    float horizontalAngle;
    float verticalAngle;
    float fov;
public:
    Camera();
    void lookAt(glm::vec3& lookVector);
    void applyTransformation();
    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();
    
    void computeVectors();
    
    glm::vec3 getLookVector() const;

    glm::vec3 getCameraPosition() const;
    void setCameraPosition(glm::vec3& cameraPosition);
    
    float getFov() const;
    void setFov(float fov);
    
    float getHorizontalAngle() const;
    void substractFromHorizontalAngle(float horizontalAngle);
    
    float getVerticalAngle() const;
    void addToVerticalAngle(float verticalAngle);
    
    glm::vec3 getUpVector() const;
    glm::vec3 getRightVector() const;
};

