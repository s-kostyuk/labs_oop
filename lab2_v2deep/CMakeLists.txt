cmake_minimum_required(VERSION 3.3)
project(lab2_v2deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES test.cpp testslib.hpp time_hm.cpp time_hm.hpp messages.hpp station.cpp station.hpp train.cpp train.hpp train_sched_item.cpp train_sched_item.hpp route.cpp route.hpp)
add_executable(lab2_v2deep ${SOURCE_FILES})