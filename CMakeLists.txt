cmake_minimum_required(VERSION 3.28)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp
        src/package_manager.cpp

        tests/func/func_sequences.cpp
        tests/func/func_hash_table.cpp
        tests/func/func_iset.cpp
        tests/func/func_package_manager.cpp

        tests/chrono/chrono_sequences.cpp
        tests/chrono/chrono_hash_table.cpp
        tests/chrono/chrono_iset.cpp

        tests/chrono/string_generator.cpp)

