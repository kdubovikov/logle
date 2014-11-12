/* 
 * File:   InputManager.h
 * Author: kdubovikov
 *
 * Created on November 4, 2014, 9:11 PM
 */
#pragma once

#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS 
#include  "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include <memory>
#include <render/Camera.h>

class InputManager {
private:
    double mouseXPos;
    double mouseYPos;
    GLfloat mouseSpeed;
    GLFWwindow* window;

public:
    InputManager(GLFWwindow* window);
    void processInputs(std::unique_ptr<Camera>& camera, double deltaTime);
};

