cmake_minimum_required(VERSION 2.8)
project(render)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../shader ../core ../input ../soil2)
add_library(render STATIC Scene.cpp Camera.cpp SimpleGeometry.cpp StaticMesh.cpp Texture.cpp MeshLoader.cpp ${CMAKE_SOURCE_DIR}/lib/libsoil2.a)

target_link_libraries(render shader input)