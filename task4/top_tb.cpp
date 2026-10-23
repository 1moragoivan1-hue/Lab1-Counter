#include "test_bench.hpp"
#include "CLI/App.hpp"
#include "vbuddy.hpp"
#include "Vtop.h"
#include <magic_enum.hpp>

int main(int argc, char **argv, char **env){
    size_t value = -1;
    
    CLI::App app("Counter TestBench");
    Vbuddy::FlagType mode = Vbuddy::FlagType::TOGGLE;

    TestBench::TBConfig config;
    config.setup(app, __FILE__);
    std::map<std::string, Vbuddy::FlagType> mode_map;
    for (auto& [val, name] : magic_enum::enum_entries<Vbuddy::FlagType>()) {
        mode_map[std::string(name)] = val; // Converts string_view to std::string
    }

    // 2. Pass the corrected map into CLI11
    app.add_option("-m,--mode", mode, "Set counting mode")
        ->transform(CLI::CheckedTransformer(mode_map, CLI::ignore_case));
    app.add_option("-v,--value", value, "Set starting value");
    CLI11_PARSE(app, argc, argv);
    Verilated::commandArgs(argc,argv);
    // init top verilog instance

    TestBench::Simulator<Vtop> sim(config.vcd_file, config.num_levels, config.trace);
    Vbuddy vbuddy("Task 4: Counter");

    sim->clk = 1;
    sim->rst = 0;
    sim->v = (value == -1) ? vbuddy.value() : value;

    vbuddy.mode(mode);
        // run simulation for many clock cycles
    for (size_t cycle = 0; config.should_stop(cycle); cycle++) {
        // dump variables into VCD file and toggle clock
        sim->en = vbuddy.flag();
        vbuddy.print_number(sim->bcd, config.digits);

        TestBench::tick(vbuddy, sim, cycle);
        if (Verilated::gotFinish()) break;
    }
}


    
