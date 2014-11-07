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

#include <vector>
#include <functional>

class Scene {
private:
    Camera* camera;
    InputManager* inputManager;
    std::vector<std::reference_wrapper<StaticMesh>> objects;
    
    //double lastTime;
public:
    void addObject(StaticMesh& object);
    void render();
    
    void setCamera(Camera* camera);
    Camera* getCamera();
    
    InputManager* getInputManager() const;
    void setInputManager(InputManager* inputManager);

};

