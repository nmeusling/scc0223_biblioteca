cmake_minimum_required(VERSION 3.5)
project(scc0223_biblioteca)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main.c
        src/menu.c
        src/dynamic/library_dynamic.c
        src/static/library_static.c
        src/dynamic/book_dynamic.c
        src/static/book_static.c
        src/dynamic/student_dynamic.c
        src/static/student_static.c
        src/input.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(scc0223_biblioteca ${SOURCE_FILES})