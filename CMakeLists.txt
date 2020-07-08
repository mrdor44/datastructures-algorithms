cmake_minimum_required(VERSION 3.15)
project(datastructures-algorithms C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(
        HEADERS
        inc/list.hpp
        inc/stack.hpp
        inc/queue.hpp
        inc/graph.hpp
        inc/tree.hpp
)

set(CUTIE_DIR Cutie)
include(${CUTIE_DIR}/Cutie.cmake)
# I set all headers as sources because I'm too lazy to specify each header for each test
add_cutie_test_target(TEST test/test_list.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_stack.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_queue.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_graph.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_tree.cpp SOURCES ${HEADERS})
add_cutie_all_tests_target()
add_cutie_coverage_targets()
