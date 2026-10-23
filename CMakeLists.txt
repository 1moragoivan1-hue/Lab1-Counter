cmake_minimum_required(VERSION 3.22)
project(verilator_labs CXX)

function(add_scoped_executable EXE_NAME)
    # Extract the current directory name (e.g., "sub1", "sub2")
    get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(UNIQUE_NAME "${DIR_NAME}_${EXE_NAME}")
    add_executable(${UNIQUE_NAME} "${EXE_NAME}_tb.cpp")
    verilate(${UNIQUE_NAME}
        SOURCES ${EXE_NAME}.sv 
        TRACE
    )
endfunction()

find_package(verilator REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(task1)
add_subdirectory(task2)