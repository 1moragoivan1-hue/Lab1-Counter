add_executable(counter counter_tb.cpp)

verilate(counter
    SOURCES counter.sv 
    TRACE
)