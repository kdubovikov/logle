cmake_minimum_required(VERSION 2.8)
project(render)

include_directories(../shader ../core ../soil2)
add_library(render STATIC SimpleGeometry.cpp TexturedGeometry.cpp Texture.cpp ${CMAKE_SOURCE_DIR}/lib/libsoil2.a)