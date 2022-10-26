cmake_minimum_required(VERSION 3.23)
project(DO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_subdirectory(src/1)
add_subdirectory(src/2)
add_subdirectory(src/3)

add_subdirectory(src/other)