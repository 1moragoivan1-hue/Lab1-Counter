#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdlib>
#include <string>
#include "CLI/CLI.hpp"

namespace TestBench{
    void eval_cycle(Vcounter* top, VerilatedVcdC* tfp, size_t cycle){
        for (int i=0; i<2; i++) {
            tfp->dump (2*cycle+i);     // unit is in ps!!!
            top->clk = !top->clk;
            top->eval ();
        }
    }
}
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

    top->clk = 1;
    top->rst = 1;
    top->en = 0;

        // run simulation for many clock cycles
    for (size_t cycle=0; cycle < num_cycles; cycle++) {
        // dump variables into VCD file and toggle clock 
        top->rst = (cycle <2) | (cycle == 15);
        top->en = (cycle>4);

        TestBench::eval_cycle(top.get(), tfp.get(), cycle);
        if (Verilated::gotFinish()) break;
    }
    tfp->close();
}


    
