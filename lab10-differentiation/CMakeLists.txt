cmake_minimum_required(VERSION 3.25)

add_executable(cm_differentiation test.cpp differentiation.h
)

target_link_libraries(
        cm_differentiation
        PUBLIC
        matrix
)

target_include_directories(
        cm_differentiation
        PUBLIC
        ../matrix
        ../lab2-Gaus
)