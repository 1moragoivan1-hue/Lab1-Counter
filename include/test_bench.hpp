#pragma once

#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.hpp"
#include "CLI/App.hpp"
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <memory>

namespace TestBench{
    struct TBConfig {
        int num_cycles{300};
        int num_levels{99};
        const char * vcd_file{""};
        bool trace{false};
        int digits = 5;

        void setup(CLI::App &app, const std::string &source_file) {
            app.option_defaults()->always_capture_default();

            vcd_file = (std::filesystem::path(source_file).stem().string() + ".vcd").c_str();
            app.add_option("-c,--cycles", num_cycles, "Number of simulation cycles");
            app.add_option("-l,--lvl", num_levels, "Number of levels");
            app.add_option("--vcd", vcd_file, "VCD output filename");
            app.add_option("--digits", digits, "Number of digits on screen");
            app.add_flag("-t,--trace", trace, "Enable signal tracing");
            
        }   
    };

    template <typename Module>
    class Simulator {
        std::unique_ptr<VerilatedVcdC> tfp;
        std::unique_ptr<Module> top;

    public:
        Simulator(const std::string& filename, int levels, bool trace) {
            Verilated::traceEverOn(trace);
            tfp = std::make_unique<VerilatedVcdC>();
            top = std::make_unique<Module>();
            top->trace(tfp.get(), levels);
            tfp->open(filename.c_str());
        }

        ~Simulator() {
            if (tfp) {
                tfp->close();
            }
        }

        Module* operator->() { return top; }
        VerilatedVcdC* get() const { return tfp.get(); }

        void tick(size_t cycle) {
            for (int i=0; i<2; i++) {
                tfp->dump (2*cycle+i);     
                top->clk = !top->clk;
                top->eval();
            }
        }
    
    };

    
    void tick(Vbuddy& vbd, auto& sim, size_t cycle) {
        vbd.tick(cycle);
        sim.tick(cycle);
    }
}

