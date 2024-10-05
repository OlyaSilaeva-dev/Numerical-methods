cmake_minimum_required(VERSION 3.25)

add_executable(matrix_test test_matrix.cpp)

target_link_libraries(matrix_test PUBLIC matrix)

target_include_directories(matrix_test PUBLIC ../../matrix)