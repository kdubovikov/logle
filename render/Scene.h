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
#include "lighting/StaticLight.h"

#include <vector>
#include <functional>

class Scene {
private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<InputManager> inputManager;
    std::vector<std::reference_wrapper<StaticMesh>> objects;
    std::vector<std::reference_wrapper<StaticLight>> lights;
    
    //double lastTime;
public:
    void addObject(StaticMesh& object);
    void render();
    void setCamera(std::unique_ptr<Camera>& camera);
    void setInputManager(std::unique_ptr<InputManager>& inputManager);
};

