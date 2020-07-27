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
        inc/graph_scanner.hpp
        inc/binary_search.hpp
        inc/array_list.hpp
        inc/merge_sort.h
)

set(CUTIE_DIR Cutie)
include(${CUTIE_DIR}/Cutie.cmake)
# I set all headers as sources because I'm too lazy to specify each header for each test
add_cutie_test_target(TEST test/test_list.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_stack.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_queue.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_graph.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_tree.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_binary_search.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_array_list.cpp SOURCES ${HEADERS})
add_cutie_test_target(TEST test/test_merge_sort.cpp SOURCES src/merge_sort.c)
add_cutie_test_target(TEST test/test_string_builder.cpp SOURCES src/string_builder.cpp)
add_cutie_all_tests_target()
add_cutie_coverage_targets()
