cmake_minimum_required(VERSION 2.8)
project(core)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB CORE_SOURCES *.cpp */*.cpp)
add_library(core STATIC ${CORE_SOURCES})