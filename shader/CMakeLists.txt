cmake_minimum_required(VERSION 2.8)
project(shader)

include_directories(../core ../glfw/include)
add_library(shader STATIC Shader.cpp ShaderManager.cpp)

