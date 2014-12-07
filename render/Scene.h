/* 
 * File:   Scene.h
 * Author: kdubovikov
 *
 * Created on November 1, 2014, 9:54 PM
 */

#pragma once
#include "geometry/Geometry.h"
#include "camera/Camera.h"
#include "input/InputManager.h"
#include "lighting/LightSource.h"
#include <vector>
#include <functional>

class Scene {
private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<LightSource> light;
    std::vector<std::reference_wrapper<Geometry>> objects;
public:
    void addObject(Geometry& object);
    void render();
    void setCamera(std::unique_ptr<Camera>& camera);
    void setInputManager(std::unique_ptr<InputManager>& inputManager);
    void setLightSource(std::unique_ptr<LightSource>& light);
};

