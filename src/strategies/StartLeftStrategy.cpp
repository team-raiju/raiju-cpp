#include "FSM.hpp"
#include "Strategy.hpp"
#include "config.hpp"

namespace raiju {

StartLeftStrategy::StartLeftStrategy() : Strategy() {
    name = "start left";
}

void StartLeftStrategy::run(FSM* fsm) {
    fsm->s_driving.drive(-50, 50);
    hal::mcu::sleep(50);

    fsm->s_driving.drive(config::maxMotorSpeed, config::maxMotorSpeed);
    hal::mcu::sleep(500);

    fsm->s_driving.drive(75, -75);
    hal::mcu::sleep(100);
}

Strategy& StartLeftStrategy::instance() {
    static StartLeftStrategy strategy;
    return strategy;
}

StartLeftStrategy::~StartLeftStrategy() {}

} // namespace raiju
