#include "vbuddy.cpp"
#include <cstdlib>

class Vbuddy {
public:
    Vbuddy(const char* title) {
        if (vbdOpen() != 1) exit(EXIT_FAILURE);
        vbdHeader(title);
    }

    ~Vbuddy() {
        vbdClose();
    }

};
