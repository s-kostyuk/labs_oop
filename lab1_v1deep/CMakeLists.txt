cmake_minimum_required(VERSION 3.3)
project(lab1_v1deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp rbtree.cpp)
add_executable(lab1_v1deep ${SOURCE_FILES})
