cmake_minimum_required(VERSION 2.8)
project(shader)

include_directories(../ ../core)
file(GLOB SHADER_SOURCES *.cpp)
add_library(shader STATIC ${SHADER_SOURCES})

target_link_libraries(shader core)