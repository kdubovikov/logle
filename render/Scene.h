/* 
 * File:   Scene.h
 * Author: kdubovikov
 *
 * Created on November 1, 2014, 9:54 PM
 */

#pragma once
#include "StaticMesh.h"
#include "Camera.h"
#include "InputManager.h"
#include "LightSource.h"
#include <vector>
#include <functional>

class Scene {
private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<LightSource> light;
    std::vector<std::reference_wrapper<StaticMesh>> objects;
public:
    void addObject(StaticMesh& object);
    void render();
    void setCamera(std::unique_ptr<Camera>& camera);
    void setInputManager(std::unique_ptr<InputManager>& inputManager);
    void setLightSource(std::unique_ptr<LightSource>& light);
};

