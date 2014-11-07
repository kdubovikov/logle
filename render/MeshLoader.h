/* 
 * File:   MeshLoader.h
 * Author: kdubovikov
 *
 * Created on November 7, 2014, 3:04 PM
 */

#pragma once
#include "StaticMesh.h"
#include <glm/glm.hpp>
#include <string.h>

class MeshLoader {
public:
    static bool load(const std::string& path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);
};

