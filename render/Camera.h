/* 
 * File:   Camera.h
 * Author: kdubovikov
 *
 * Created on November 1, 2014, 10:13 PM
 */
#pragma once
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 cameraPosition;
    glm::vec3 lookVector;
public:
    Camera();
    void lookAt(glm::vec3& lookVector);
    void translate(glm::vec3& cameraPosition);
    void applyTransformation();
    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();
};

