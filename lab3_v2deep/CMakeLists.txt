cmake_minimum_required(VERSION 3.4)
project(lab3_v2deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES
        testslib.hpp
        realization/element.hpp
        realization/unary_element.cpp
        realization/unary_element.hpp
        realization/binary_element.cpp
        realization/binary_element.hpp
        realization/input_port_element.cpp
        realization/input_port_element.hpp
        realization/port.hpp
        realization/input_port.hpp
        realization/output_port.cpp
        realization/output_port.hpp
        realization/messages.hpp
        realization/combinational_circuit.cpp
        realization/combinational_circuit.hpp
        realization/port.cpp
        realization/all_elements.hpp
        realization/all_ports.hpp
        realization/input_port.cpp
        circuit_test_lib.cpp
        circuit_test_lib.hpp
        tested_circuits.cpp
        tested_circuits.hpp
        #test_blocks.cpp
        test_circuit.cpp
    )

add_executable(lab3_v2deep ${SOURCE_FILES})