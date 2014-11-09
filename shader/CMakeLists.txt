cmake_minimum_required(VERSION 2.8)
project(shader)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../core ../glfw/include)
add_library(shader STATIC ShaderManager.cpp Shader.cpp UniformManager.cpp)