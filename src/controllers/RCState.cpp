#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

// TODO: isso deveria estar na classe, tirar a definição padrão State (o define) para poder colocar
// esse tipo de variável privada
static uint32_t ticker = 0; // TODO: Adapter > SoftTimer
static bool leaving = false;

void FSM::RCState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:rc");
    ticker = mcu::get_tick();
}

void FSM::RCState::cycle(FSM* fsm) {
    auto ch4 = fsm->s_radio.get_ch4();
    if ((ch4 < 1250 || ch4 > 1750) && !leaving) {
        ticker = mcu::get_tick();
        leaving = true;
    }

    if (ch4 >= 1250 && ch4 <= 1750) {
        leaving = false;
    }

    if (leaving && mcu::get_tick() - ticker >= 1000) {
        fsm->set_state(IdleState::instance());
        return;
    }

    auto coords = fsm->s_radio.coordinates();

    auto mot1 = coords.y + coords.x;
    auto mot2 = coords.y - coords.x;

    if (fsm->s_radio.get_ch3() > 1500) {
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
