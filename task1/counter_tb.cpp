#include "CLI/App.hpp"
#include "test_bench.hpp"

int main(int argc, char **argv, char **env){

    size_t wait_time = 3;
    size_t stop = 0x9;
    CLI::App app("Counter TestBench");
    
    TestBench::TBConfig config;
    config.setup(app, __FILE__);
    app.add_option("--wait", wait_time, "Wait Time");
    app.add_option("--stop", stop, "cycle to stop counting at");
    CLI11_PARSE(app, argc, argv);
    Verilated::commandArgs(argc,argv);
    // init top verilog instance

    TestBench::Simulator<Vcounter> sim(config.vcd_file, config.num_levels, config.trace);

    sim->clk = 1;
    sim->rst = 0;
    sim->en = 0;

        // run simulation for many clock cycles
    for (size_t cycle = 0; cycle < config.num_cycles; cycle++) {
        // dump variables into VCD file and toggle clock 
  
        sim->en = ((cycle < stop) | (cycle >= (stop + wait_time)));

        sim.tick(cycle);
        if (Verilated::gotFinish()) break;
    }
}


    
