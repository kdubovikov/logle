/* 
 * File:   Scene.h
 * Author: kdubovikov
 *
 * Created on November 1, 2014, 9:54 PM
 */

#pragma once
#include "TexturedGeometry.h"
#include "Camera.h"
#include "InputManager.h"

#include <vector>
#include <functional>

class Scene {
private:
    Camera* camera;
    InputManager* inputManager;
    std::vector<std::reference_wrapper<TexturedGeometry>> objects;
    
    //double lastTime;
public:
    void addObject(TexturedGeometry& object);
    void render();
    
    void setCamera(Camera* camera);
    Camera* getCamera();
    
    InputManager* getInputManager() const;
    void setInputManager(InputManager* inputManager);

};

