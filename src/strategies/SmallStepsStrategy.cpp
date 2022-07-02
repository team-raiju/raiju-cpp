#include "FSM.hpp"
#include "Strategy.hpp"
#include "config.hpp"

namespace raiju {

SmallStepsStrategy::SmallStepsStrategy() : Strategy(), attackTicker(3000), stepTicker(3000) {
    name = "small steps";
    still = false;
    attacking = false;
}

void SmallStepsStrategy::run(FSM* fsm) {
    if (fsm->s_line.is_white(LineService::FR1) || fsm->s_line.is_white(LineService::FL1)) {
        fsm->s_driving.drive(-config::reverseSpeed, -config::reverseSpeed);
        hal::mcu::sleep(config::reverseTimeMs); // TODO: Calibração desses valores de tempo de volta pras curvas

        int8_t mult = fsm->s_line.is_white(LineService::FR1) ? -1 : 1;
        fsm->s_driving.drive(config::turnSpeed * mult, -config::turnSpeed * mult);
        hal::mcu::sleep(config::turnTimeMs);
    }

    if (fsm->s_distance.is_reading(DistanceService::F) ||
        (fsm->s_distance.is_reading(DistanceService::R) && fsm->s_distance.is_reading(DistanceService::L))) {
        fsm->s_driving.drive(100, 100);
        still = false;
        if (!attacking) {
            attacking = true;
            attackTicker.reset();
        }
    } else if (fsm->s_distance.is_reading(DistanceService::R)) {
        fsm->s_driving.drive(75, 30);
        still = false;
        attacking = false;
    } else if (fsm->s_distance.is_reading(DistanceService::L)) {
        fsm->s_driving.drive(30, 75);
        still = false;
        attacking = false;
    } else if (fsm->s_distance.is_reading(DistanceService::FR)) {
        fsm->s_driving.drive(75, -75);
        still = false;
        attacking = false;
    } else if (fsm->s_distance.is_reading(DistanceService::FL)) {
        fsm->s_driving.drive(-75, 75);
        still = false;
        attacking = false;
    } else {
        if (!still) {
            still = true;
            stepTicker.reset();
        }
        fsm->s_driving.drive(0, 0);
        attacking = false;
    }

    if (still && stepTicker.expired()) {
        still = false;
        fsm->s_driving.drive(50, 50);
        hal::mcu::sleep(config::stepWaitTimeMs);
    }

    if (attacking && attackTicker.expired()) {
        attacking = false;
        fsm->s_driving.drive(-50, -50);
        hal::mcu::sleep(config::stepWaitTimeMs);
    }
}

Strategy& SmallStepsStrategy::instance() {
    static SmallStepsStrategy strategy;
    return strategy;
}

SmallStepsStrategy::~SmallStepsStrategy() {}

} // namespace raiju
