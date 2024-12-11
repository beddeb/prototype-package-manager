cmake_minimum_required(VERSION 3.28)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp
        src/package_manager.cpp

        tests/func/test_sequence.cpp
        tests/func/test_list_sequence.cpp
        tests/func/test_array_sequence.cpp
        tests/func/test_hash_table.cpp
        tests/func/test_iset.cpp
        tests/func/test_package_manager.cpp

        tests/chrono/chrono_sequences.cpp)

