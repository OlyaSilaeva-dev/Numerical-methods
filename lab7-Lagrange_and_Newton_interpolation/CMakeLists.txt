cmake_minimum_required(VERSION 3.25)

add_executable(cm_Lagrange_and_Newton_interpolation test.cpp interpolations.h
)

target_link_libraries(
        cm_Lagrange_and_Newton_interpolation
        PUBLIC
        matrix
)

target_include_directories(
        cm_Lagrange_and_Newton_interpolation
        PUBLIC
        ../matrix
)