cmake_minimum_required(VERSION 3.25)

add_executable(cm_mnk test.cpp mnk.h
)

target_link_libraries(
        cm_mnk
        PUBLIC
        matrix
)

target_include_directories(
        cm_mnk
        PUBLIC
        ../matrix
        ../lab2-Gaus
)