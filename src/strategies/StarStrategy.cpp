#include "FSM.hpp"
#include "Strategy.hpp"
#include "config.hpp"

namespace raiju {

StarStrategy::StarStrategy() : Strategy() {}

void StarStrategy::run(FSM* fsm) {
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
    } else if (fsm->s_distance.is_reading(DistanceService::Position::BRIGHT)) {
        fsm->s_driving.drive(75, 30);
    } else if (fsm->s_distance.is_reading(DistanceService::Position::BLEFT)) {
        fsm->s_driving.drive(30, 75);
    } else if (fsm->s_distance.is_reading(DistanceService::Position::RIGHT)) {
        fsm->s_driving.drive(75, -75);
    } else if (fsm->s_distance.is_reading(DistanceService::Position::LEFT)) {
        fsm->s_driving.drive(-75, 75);
    } else {
        fsm->s_driving.drive(60, 60);
    }
}

Strategy& StarStrategy::instance() {
    static StarStrategy strategy;
    return strategy;
}

StarStrategy::~StarStrategy() {}

} // namespace raiju
