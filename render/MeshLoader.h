/* 
 * File:   MeshLoader.h
 * Author: kdubovikov
 *
 * Created on November 7, 2014, 3:04 PM
 */

#pragma once
#include "StaticMesh.h"

class MeshLoader {
public:
    static TexturedGeometry load(const std::string& path);
};

