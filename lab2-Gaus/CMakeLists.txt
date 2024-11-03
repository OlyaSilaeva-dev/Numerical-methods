cmake_minimum_required(VERSION 3.25)

add_executable(cm_gaus_test test.cpp Gaus.h
        ../lab4-Rotation_method/Rotation_method.h
        ../lab4-Rotation_method/test.cpp)

target_link_libraries(
        cm_gaus_test
        PUBLIC
        matrix
)

target_include_directories(
        cm_gaus_test
        PUBLIC
        ../matrix
)