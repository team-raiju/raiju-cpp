#include "FSM.hpp"
#include "Strategy.hpp"
#include "config.hpp"

namespace raiju {

StartLeftStrategy::StartLeftStrategy() : Strategy() {
    name = "start left";
}

void StartLeftStrategy::run(FSM* fsm) {
    // fsm->s_driving.drive(-100, 100);
    // hal::mcu::sleep(50);

    // fsm->s_driving.drive(100, 75);
    // hal::mcu::sleep(220);

    // fsm->s_driving.drive(75, -75);
    // hal::mcu::sleep(45);

    fsm->s_driving.drive(100, -100);
    hal::mcu::sleep(40);

    fsm->s_driving.drive(65, 100);
    hal::mcu::sleep(240);

    fsm->s_driving.drive(-75, 75);
    hal::mcu::sleep(45);
}

Strategy& StartLeftStrategy::instance() {
    static StartLeftStrategy strategy;
    return strategy;
}

StartLeftStrategy::~StartLeftStrategy() {}

} // namespace raiju
