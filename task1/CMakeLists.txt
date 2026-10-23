add_executable(task1_counter counter_tb.cpp)

verilate(task1_counter
    SOURCES counter.sv 
    TRACE
)