cmake_minimum_required(VERSION 3.25)

add_executable(cm_rotation_method_test test.cpp Rotation_method.h
)

target_link_libraries(
        cm_rotation_method_test
        PUBLIC
        matrix
)

target_include_directories(
        cm_rotation_method_test
        PUBLIC
        ../matrix
)