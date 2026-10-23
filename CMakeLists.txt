cmake_minimum_required(VERSION 3.12)
project(verilator_labs CXX)

find_package(verilator REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(task1)