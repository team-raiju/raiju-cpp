#include "main.h"

#include "FSM.hpp"
#include "hal.hpp"

namespace mcu = hal::mcu;
using raiju::FSM;

int main() {
    mcu::init();

    FSM fsm;
    fsm.init();

    for (;;) {
        fsm.cycle();
    }
}
