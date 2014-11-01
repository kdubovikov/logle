/* 
 * File:   Scene.h
 * Author: kdubovikov
 *
 * Created on November 1, 2014, 9:54 PM
 */

#pragma once
#include "TexturedGeometry.h"
#include "Camera.h"

#include <vector>
#include <functional>

class Scene {
private:
    Camera camera;
    std::vector<std::reference_wrapper<TexturedGeometry>> objects;
public:
    void addObject(TexturedGeometry& object);
    void render();
    void setCamera(Camera& camera);
    Camera& getCamera();
};

