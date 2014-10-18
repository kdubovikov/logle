cmake_minimum_required(VERSION 2.8)
project(shader)

include_directories(../glfw/include)
add_library(shader STATIC shader.cpp)
