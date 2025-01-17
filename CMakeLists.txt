cmake_minimum_required(VERSION 3.28)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(lab3 main.cpp
        src/package_manager.cpp

        tests/func/func_sequences.cpp
        tests/func/func_hash_table.cpp
        tests/func/func_iset.cpp
        tests/func/func_package_manager.cpp

        tests/chrono/chrono_sequences.cpp
        tests/chrono/chrono_hash_table.cpp
        tests/chrono/chrono_iset.cpp

        tests/chrono/string_generator.cpp
        tests/chrono/demangle.cpp

        graphics/plot.cpp
        graphics/vis_dep.cpp)

set(SFML_DIR externallibs/sfml/sfmlx64win/SFML-2.6.1/lib/cmake/SFML)

target_link_libraries(lab3 sfml-graphics)

find_package(SFML 2.6.1 REQUIRED graphics window system)