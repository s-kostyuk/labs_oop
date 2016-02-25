cmake_minimum_required(VERSION 3.3)
project(lab3_v2deep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES
        testslib.hpp
        implementation/element.hpp
        implementation/unary_element.cpp
        implementation/unary_element.hpp
        implementation/binary_element.cpp
        implementation/binary_element.hpp
        implementation/input_port_element.cpp
        implementation/input_port_element.hpp
        implementation/port.hpp
        implementation/input_port.hpp
        implementation/output_port.cpp
        implementation/output_port.hpp
        implementation/messages.hpp
        implementation/combinational_circuit.cpp
        implementation/combinational_circuit.hpp
        implementation/port.cpp
        implementation/all_elements.hpp
        implementation/all_ports.hpp
        implementation/input_port.cpp
        circuit_test_lib.cpp
        circuit_test_lib.hpp
        sample_circuits.cpp
        sample_circuits.hpp
        #test_units.cpp
        test_circuit.cpp
        controller.cpp controller.hpp)

add_executable(lab3_v2deep ${SOURCE_FILES})