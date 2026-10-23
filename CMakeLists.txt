cmake_minimum_required(VERSION 3.12)
project(verilator_labs CXX)

find_package(verilator REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(task1)
add_subdirectory(task2)