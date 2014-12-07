cmake_minimum_required(VERSION 2.8)
project(render)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(UNIX)
    set(RENDER_DEPS "${LOGLE_UNIX_DEPS}")
elseif(WINDOWS)
    set(RENDER_DEPS "${LOGLE_WINDOWS_DEPS}")
endif()

file(GLOB RENDER_SOURCES *.cpp */*.cpp)
include_directories(. camera lighting model text geometry ../)
add_library(render STATIC ${RENDER_SOURCES})

target_link_libraries(render shader input ${RENDER_DEPS})
