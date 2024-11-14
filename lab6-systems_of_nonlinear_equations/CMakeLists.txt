cmake_minimum_required(VERSION 3.25)

add_executable(cm_systems_of_nonlinear_equations_test test.cpp methods.h
)

target_link_libraries(
        cm_systems_of_nonlinear_equations_test
        PUBLIC
        matrix
)

target_include_directories(
        cm_systems_of_nonlinear_equations_test
        PUBLIC
        ../matrix
)