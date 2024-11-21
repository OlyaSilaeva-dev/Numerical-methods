cmake_minimum_required(VERSION 3.25)

add_executable(cm_cubic_spline test.cpp spline.h
)

target_link_libraries(
        cm_cubic_spline
        PUBLIC
        matrix
)

target_include_directories(
        cm_cubic_spline
        PUBLIC
        ../matrix
        ../lab1-Progonka
)