cmake_minimum_required(VERSION 3.4)
project(lab3_v2deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES
        test.cpp
        testslib.hpp
        element.hpp
        unary_element.cpp
        unary_element.hpp
        binary_element.cpp
        binary_element.hpp
        input_port_element.cpp
        input_port_element.hpp
        port.hpp
        input_port.hpp
        output_port.cpp
        output_port.hpp
        messages.hpp)

add_executable(lab3_v2deep ${SOURCE_FILES})