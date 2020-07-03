cmake_minimum_required(VERSION 3.15)
project(datastructures-algorithms C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CUTIE_DIR Cutie)
include(${CUTIE_DIR}/Cutie.cmake)
add_cutie_tests_target(
        test/test_list.cpp
        test/test_stack.cpp
        test/test_queue.cpp
        test/test_graph.cpp
        inc/list.hpp
        inc/stack.hpp
        inc/queue.hpp
        inc/graph.hpp)
