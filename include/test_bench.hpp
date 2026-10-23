#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdlib>
#include <string>


namespace TestBench{
    void eval_cycle(Vcounter* top, VerilatedVcdC* tfp, size_t cycle) {
        for (int i=0; i<2; i++) {
            tfp->dump (2*cycle+i);     
            top->clk = !top->clk;
            top->eval ();
        }
    }
}