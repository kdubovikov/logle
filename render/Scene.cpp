/* 
 * File:   Scene.cpp
 * Author: kdubovikov
 * 
 * Created on November 1, 2014, 9:54 PM
 */

#include "Scene.h"

void Scene::addObject(StaticMesh& object) {
    objects.push_back(object);
}

void Scene::render() {
    static double lastTime = glfwGetTime();
    
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    
    inputManager.get()->processInputs(camera, deltaTime);
    camera.get()->applyTransformation();
    
    for (StaticMesh& object : objects) {
        object.applyTransformation(camera.get()->getViewMatrix(), camera.get()->getProjectionMatrix());
        object.prepareLightSource(light);
        object.render();
    }
    
    lastTime = currentTime;
}

void Scene::setCamera(std::unique_ptr<Camera>& camera) {
    this->camera = std::move(camera);
}

void Scene::setInputManager(std::unique_ptr<InputManager>& inputManager) {
    this->inputManager = std::move(inputManager);
}

void Scene::setLightSource(std::unique_ptr<LightSource>& light) {
    this->light = std::move(light);
}

