add_executable(task2_counter counter_tb.cpp)

verilate(task2_counter
    SOURCES counter.sv 
    TRACE
)