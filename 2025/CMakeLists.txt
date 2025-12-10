cmake_minimum_required(VERSION 3.10)
project(2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(2025 day-1/main.cpp
        day-2/main.cpp)

# Copy input file to build directory when you build
configure_file(${CMAKE_SOURCE_DIR}/day-1/input.txt
        ${CMAKE_BINARY_DIR}/input.txt COPYONLY)
