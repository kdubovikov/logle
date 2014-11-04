cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -std=c++11")
project(input)

include_directories(../render  ../glfw/include)
add_library(input STATIC InputManager.cpp)

