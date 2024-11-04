cmake_minimum_required(VERSION 3.25)

add_executable(cm_4methods_for_nonlinear_equations test.cpp methods.h
)

target_link_libraries(
        cm_4methods_for_nonlinear_equations
        PUBLIC
        matrix
)

target_include_directories(
        cm_4methods_for_nonlinear_equations
        PUBLIC
        ../matrix
)