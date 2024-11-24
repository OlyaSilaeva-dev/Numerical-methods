cmake_minimum_required(VERSION 3.25)

add_executable(cm_Causy_problem test.cpp Causy_problem.h
)

target_link_libraries(
        cm_Causy_problem
        PUBLIC
        matrix
)

target_include_directories(
        cm_Causy_problem
        PUBLIC
        ../matrix
        ../lab2-Gaus
)