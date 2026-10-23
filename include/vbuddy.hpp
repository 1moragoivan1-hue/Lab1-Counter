#pragma once

#include "vbuddy.cpp"
#include <cstdlib>
class Vbuddy {
public:

    enum class FlagType : int {
        TOGGLE,
        ARMED
    };

    Vbuddy(const char* title) {
        if (vbdOpen() != 1) exit(EXIT_FAILURE);
        vbdHeader(title);
    }

    template <typename T>
    void print_number(T num, int digits) {
        for (int i = 1; i <= digits; i++){
            vbdHex(i, (int(num) >>  ((i - 1) * 4)) & 0xF);
        }
    }

    void tick(int cycle) {
        vbdCycle(cycle + 1);
    }

    bool flag() {
        return vbdFlag();
    }

    uint value() {
        return vbdValue();
    }

    void mode(FlagType flag) {
        vbdSetMode((int)flag);

    }

    ~Vbuddy() {
        vbdClose();
    }
};
