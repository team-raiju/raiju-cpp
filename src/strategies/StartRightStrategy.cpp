#include "FSM.hpp"
#include "Strategy.hpp"
#include "config.hpp"

namespace raiju {

StartRightStrategy::StartRightStrategy() : Strategy() {
    name = "start right";
}

void StartRightStrategy::run(FSM* fsm) {
    fsm->s_driving.drive(100, -100);
    hal::mcu::sleep(40);

    fsm->s_driving.drive(65, 100);
    hal::mcu::sleep(240);

    fsm->s_driving.drive(-75, 75);
    hal::mcu::sleep(45);
}

Strategy& StartRightStrategy::instance() {
    static StartRightStrategy strategy;
    return strategy;
}

StartRightStrategy::~StartRightStrategy() {}

} // namespace raiju
