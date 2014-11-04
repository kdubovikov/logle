/* 
 * File:   InputManager.cpp
 * Author: kdubovikov
 * 
 * Created on November 4, 2014, 9:11 PM
 */

#include "InputManager.h"

InputManager::InputManager(Camera* camera, GLFWwindow* window) :
camera(camera),
window(window),
mouseSpeed(0.005f) {
}

void InputManager::processInputs(double deltaTime) {
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    
    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
    
    GLfloat horizontalAngleDelta =  mouseSpeed * float(windowWidth / 2 - mouseXPos);
    GLfloat verticalAngleDelta =  mouseSpeed * float(windowHeight / 2 - mouseYPos);
    
    camera->substractFromHorizontalAngle(horizontalAngleDelta);
    camera->addToVerticalAngle(verticalAngleDelta);
    camera->computeVectors();

    glm::vec3 lookVector = camera->getLookVector();
    glm::vec3 right = camera->getRightVector();
    glm::vec3 position = camera->getCameraPosition();
    
    if (glfwGetKey(window, GLFW_KEY_W)) {
        position += lookVector * float(deltaTime * 3.0f);
    } else if (glfwGetKey(window, GLFW_KEY_S)) {
        position -= lookVector * float(deltaTime * 3.0f);
    } else if (glfwGetKey(window, GLFW_KEY_D)) {
        position += right * float(deltaTime * 3.0f);
    } else if (glfwGetKey(window, GLFW_KEY_A)) {
        position -= right * float(deltaTime * 3.0f);
    }
    
    camera->setCameraPosition(position);
}


