cmake_minimum_required(VERSION 3.28)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp
        src/package_manager.cpp

        tests/test_sequence.cpp
        tests/test_list_sequence.cpp
        tests/test_array_sequence.cpp
        tests/test_hash_table.cpp
        tests/test_iset.cpp
        tests/test_package_manager.cpp)
