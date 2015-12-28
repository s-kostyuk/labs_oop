cmake_minimum_required(VERSION 3.4)
project(lab3_v2deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES
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
        messages.hpp
        combinational_circuit.cpp
        combinational_circuit.hpp
        port.cpp
        all_elements.hpp
        all_ports.hpp
        input_port.cpp
        test_blocks.cpp
        #test_circuit.cpp
        circuit_test_lib.cpp circuit_test_lib.hpp tested_circuits.cpp tested_circuits.hpp)

add_executable(lab3_v2deep ${SOURCE_FILES})