cmake_minimum_required(VERSION 3.25)

add_executable(cm_integration test.cpp integration.h
)

target_link_libraries(
        cm_integration
        PUBLIC
        matrix
)

target_include_directories(
        cm_integration
        PUBLIC
        ../matrix
        ../lab2-Gaus
)