#include "test_bench.hpp"
#include "CLI/App.hpp"
#include "vbuddy.hpp"
#include "Vcounter.h"

int main(int argc, char **argv, char **env){
    CLI::App app("Counter TestBench");
    Vbuddy::FlagType mode = Vbuddy::FlagType::TOGGLE;

    TestBench::TBConfig config;
    config.setup(app, __FILE__);
    app.add_option("--mode", mode, "Toggle between counting modes")
        ->check(CLI::Range(0, 1));
    CLI11_PARSE(app, argc, argv);
    Verilated::commandArgs(argc,argv);
    // init top verilog instance

    TestBench::Simulator<Vcounter> sim(config.vcd_file, config.num_levels, config.trace);
    Vbuddy vbuddy("Task3: Counter");

    sim->clk = 1;
    sim->rst = 0;
    sim->en = 0;
    sim->v = vbuddy.value();

    vbuddy.mode(mode);
        // run simulation for many clock cycles
    for (size_t cycle = 0; cycle < config.num_cycles; cycle++) {
        // dump variables into VCD file and toggle clock
        sim->ld = (cycle == 0);
        sim->en = vbuddy.flag();

        vbuddy.print_number(sim->count, config.digits);
        

        TestBench::tick(vbuddy, sim, cycle);
        if (Verilated::gotFinish()) break;
    }
}


    
