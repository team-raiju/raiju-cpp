#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

FSM::RCState::RCState() : leaveTicker(1000) {
    this->leaving = false;
}

void FSM::RCState::enter(FSM* fsm) {
    fsm->s_bt.transmit("state:RC");
    leaveTicker.reset();
}

void FSM::RCState::cycle(FSM* fsm) {
    auto ch4 = fsm->s_radio.get_ch4();
    if ((ch4 < 1250 || ch4 > 1750) && !leaving) {
        leaveTicker.reset();
        leaving = true;
    }

    if (ch4 >= 1250 && ch4 <= 1750) {
        leaving = false;
    }

    if (leaving && leaveTicker.expired()) {
        fsm->set_state(IdleState::instance());
        return;
    }

    auto coords = fsm->s_radio.coordinates();

    auto mot1 = coords.y + coords.x;
    auto mot2 = coords.y - coords.x;

    if (fsm->s_radio.get_ch3() > 1800 && coords.y > 60) {
        if (fsm->s_line.is_white(LineService::Position::FR1) || fsm->s_line.is_white(LineService::Position::FL1)) {
            fsm->s_driving.drive(-100, -100);
            mcu::sleep(150); // TODO: Calibração desses valores de tempo de volta pras curvas

            int8_t mult = fsm->s_line.is_white(LineService::Position::FR1) ? -1 : 1;
            fsm->s_driving.drive(75 * mult, -75 * mult);
            mcu::sleep(100);
        }

        if (fsm->s_distance.is_reading(DistanceService::Position::FRONT) ||
            (fsm->s_distance.is_reading(DistanceService::Position::BRIGHT) &&
             fsm->s_distance.is_reading(DistanceService::Position::BLEFT))) {
            mot1 = mot2 = 100;
        } else if (fsm->s_distance.is_reading(DistanceService::Position::BRIGHT)) {
            mot1 = 75;
            mot2 = 30;
        } else if (fsm->s_distance.is_reading(DistanceService::Position::BLEFT)) {
            mot1 = 30;
            mot2 = 75;
        } else if (fsm->s_distance.is_reading(DistanceService::Position::RIGHT)) {
            mot1 = 75;
            mot2 = -75;
        } else if (fsm->s_distance.is_reading(DistanceService::Position::LEFT)) {
            mot1 = -75;
            mot2 = 75;
        } else {
            mot1 = mot2 = 60;
        }
    } else if (fsm->s_radio.get_ch3() > 1500) {
        if (fsm->s_line.is_white(LineService::Position::FR1) || fsm->s_line.is_white(LineService::Position::FL1)) {
            mot1 = mot2 = -100;
        } else if (fsm->s_line.is_white(LineService::Position::BR) || fsm->s_line.is_white(LineService::Position::BL)) {
            mot1 = mot2 = 100;
        }
    }

    fsm->s_driving.drive(mot1, mot2);
}

void FSM::RCState::exit(FSM* fsm) {
    fsm->s_driving.stop();
}

FSM::State& FSM::RCState::instance() {
    static RCState s;
    return s;
}

FSM::RCState::~RCState() {}

} // namespace raiju
