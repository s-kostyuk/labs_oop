cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(PROJECT_NAME proof_of_concept)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES bstree.cpp computation_time.cpp )
set(SOURCE_FILES ${SOURCE_FILES} bstree_test.cpp bstree_symm_walk_alternative.cpp)

set(COMP_FILES_FOLDER /home/srg/code/labs_sta/lab3_v1deep)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})