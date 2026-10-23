#include "test_bench.hpp"
#include "CLI/CLI.hpp"
#include "vbuddy.hpp"



int main(int argc, char **argv, char **env){
    int num_cycles{};
    int num_levels{};
    
    CLI::App app("Counter TestBench");
    app.add_option("--cycles", num_cycles, "Number of cycles")->default_val(300);
    app.add_option("--lvl", num_levels, "Number of levels")->default_val(99);

    Verilated::commandArgs(argc,argv);
    // init top verilog instance
    

    auto top = std::make_unique<Vcounter>();
    auto tfp = std::make_unique<VerilatedVcdC>();
    //init trace dump
    Verilated::traceEverOn(true);

    top->trace(tfp.get(), num_levels);
    tfp->open("counter.vcd");

    Vbuddy vbd("Task1: Counter");

    top->clk = 1;
    top->rst = 1;
    top->en = 0;

        // run simulation for many clock cycles
    for (size_t cycle=0; cycle < num_cycles; cycle++) {
        // dump variables into VCD file and toggle clock 
        vbdHex(4, (int(top->count) >> 12) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, (int(top->count)) & 0xF);
        vbdCycle(cycle+1);
        
        
        top->rst = (cycle <2) | (cycle == 15);
        top->en = vbdFlag();

        TestBench::eval_cycle(top.get(), tfp.get(), cycle);
        if (Verilated::gotFinish()) break;
    }

    

    tfp->close();
}


    
