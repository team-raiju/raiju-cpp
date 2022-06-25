#include "FSM.hpp"
#include "Strategy.hpp"
#include "config.hpp"

namespace raiju {

SmallStepsStrategy::SmallStepsStrategy() : Strategy() {
    still = false;
}

void SmallStepsStrategy::run(FSM* fsm) {
    if (fsm->s_line.is_white(LineService::Position::FR1) || fsm->s_line.is_white(LineService::Position::FL1)) {
        fsm->s_driving.drive(-config::reverseSpeed, -config::reverseSpeed);
        hal::mcu::sleep(config::reverseTimeMs); // TODO: Calibração desses valores de tempo de volta pras curvas

        int8_t mult = fsm->s_line.is_white(LineService::Position::FR1) ? -1 : 1;
        fsm->s_driving.drive(config::turnSpeed * mult, -config::turnSpeed * mult);
        hal::mcu::sleep(config::turnTimeMs);
    }

    if (fsm->s_distance.is_reading(DistanceService::Position::FRONT) ||
        (fsm->s_distance.is_reading(DistanceService::Position::BRIGHT) &&
         fsm->s_distance.is_reading(DistanceService::Position::BLEFT))) {
        fsm->s_driving.drive(100, 100);
        still = false;
    } else if (fsm->s_distance.is_reading(DistanceService::Position::BRIGHT)) {
        fsm->s_driving.drive(75, 30);
        still = false;
    } else if (fsm->s_distance.is_reading(DistanceService::Position::BLEFT)) {
        fsm->s_driving.drive(30, 75);
        still = false;
    } else if (fsm->s_distance.is_reading(DistanceService::Position::RIGHT)) {
        fsm->s_driving.drive(75, -75);
        still = false;
    } else if (fsm->s_distance.is_reading(DistanceService::Position::LEFT)) {
        fsm->s_driving.drive(-75, 75);
        still = false;
    } else {
        if (!still) {
            still = true;
            stepTicker.reset();
        }
        fsm->s_driving.drive(0, 0);
    }

    if (still && stepTicker.get() >= 3000) {
        still = false;
        fsm->s_driving.drive(50, 50);
        hal::mcu::sleep(config::stepWaitTimeMs);
    }
}

Strategy& SmallStepsStrategy::instance() {
    static SmallStepsStrategy strategy;
    return strategy;
}

SmallStepsStrategy::~SmallStepsStrategy() {}

} // namespace raiju
