cmake_minimum_required(VERSION 3.25)

add_executable(cm_simple_iteration_method_test test.cpp simple_iteration_method.h
)

target_link_libraries(
        cm_simple_iteration_method_test
        PUBLIC
        matrix
)

target_include_directories(
        cm_simple_iteration_method_test
        PUBLIC
        ../matrix
)