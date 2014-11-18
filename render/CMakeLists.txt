cmake_minimum_required(VERSION 2.8)
project(render)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(UNIX)
    set(RENDER_DEPS "${LOGLE_UNIX_DEPS}")
elseif(WINDOWS)
    set(RENDER_DEPS "${LOGLE_WINDOWS_DEPS}")
endif()

include_directories(../ ../core ../shader ../input)
add_library(render STATIC Scene.cpp Camera.cpp StaticMesh.cpp Texture.cpp MeshLoader.cpp LightSource.cpp)

target_link_libraries(render shader input  ${RENDER_DEPS})
