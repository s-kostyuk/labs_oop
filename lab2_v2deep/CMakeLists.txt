cmake_minimum_required(VERSION 3.3)
project(lab2_v2deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES
        libs/controller.cpp
        libs/controller.hpp
        libs/messages.hpp
        libs/route.cpp
        libs/route.hpp
        libs/route_iterators.cpp
        libs/station.cpp
        libs/station.hpp
        libs/time_hm.cpp
        libs/time_hm.hpp
        libs/train.cpp
        libs/train.hpp
        libs/train_sched_item.cpp
        libs/train_sched_item.hpp
        test.cpp
        testslib.hpp
        libs/controller_prints.cpp
    )

add_executable(lab2_v2deep ${SOURCE_FILES})