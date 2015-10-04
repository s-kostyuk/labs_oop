cmake_minimum_required(VERSION 3.3)
project(lab1_v1deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES test.cpp libs/rbtree.cpp libs/integerset.cpp libs/integerset.hpp)
add_executable(lab1_v1deep ${SOURCE_FILES})
