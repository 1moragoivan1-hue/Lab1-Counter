#include "CLI/App.hpp"
#include "test_bench.hpp"

int main(int argc, char **argv, char **env){
    CLI::App app("Counter TestBench");
    
    TestBench::TBConfig config;
    config.setup(app, __FILE__);

    CLI11_PARSE(app, argc, argv);
    Verilated::commandArgs(argc,argv);
    // init top verilog instance

    TestBench::Simulator<Vcounter> sim(config.vcd_file, config.num_levels, config.trace);

    sim->clk = 1;
    sim->rst = 1;
    sim->en = 0;

        // run simulation for many clock cycles
    for (size_t cycle = 0; cycle < config.num_cycles; cycle++) {
        // dump variables into VCD file and toggle clock 
        sim->rst = (cycle <2) | (cycle == 15);
        sim->en = (cycle>4);

        sim.tick(cycle);
        if (Verilated::gotFinish()) break;
    }
}


    
