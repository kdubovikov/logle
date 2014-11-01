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
    camera.applyTransformation();
    
    for (TexturedGeometry& object : objects) {
        object.applyTransformation(camera.getViewMatrix(), camera.getProjectionMatrix());
        object.render();
    }
}

Camera& Scene::getCamera() {
    return camera;
}

void Scene::setCamera(Camera& camera) {
    this->camera = camera;
}



