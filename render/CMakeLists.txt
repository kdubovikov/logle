cmake_minimum_required(VERSION 2.8)
project(render)

include_directories(../shader ../core)
add_library(render STATIC SimpleGeometry.cpp)