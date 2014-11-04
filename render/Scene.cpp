/* 
 * File:   Scene.cpp
 * Author: kdubovikov
 * 
 * Created on November 1, 2014, 9:54 PM
 */

#include "Scene.h"

void Scene::addObject(TexturedGeometry& object) {
    objects.push_back(object);
}

void Scene::render() {
    static double lastTime = glfwGetTime();
    
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    
    inputManager->processInputs(deltaTime);
    camera->applyTransformation();
    
    for (TexturedGeometry& object : objects) {
        object.applyTransformation(camera->getViewMatrix(), camera->getProjectionMatrix());
        object.render();
    }
    
    lastTime = currentTime;
}

Camera* Scene::getCamera() {
    return camera;
}

void Scene::setCamera(Camera* camera) {
    this->camera = camera;
}

InputManager* Scene::getInputManager() const {
    return inputManager;
}

void Scene::setInputManager(InputManager* inputManager) {
    this->inputManager = inputManager;
}