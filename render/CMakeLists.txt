cmake_minimum_required(VERSION 2.8)
project(render)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../shader ../core ../soil2)
add_library(render STATIC Scene.cpp Camera.cpp SimpleGeometry.cpp TexturedGeometry.cpp Texture.cpp ${CMAKE_SOURCE_DIR}/lib/libsoil2.a)

target_link_libraries(render shader)