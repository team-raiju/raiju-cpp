#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

void FSM::InitState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:init");

    fsm->s_driving.stop();
    fsm->s_line.start();

    fsm->s_led.purple_charge();
}

void FSM::InitState::cycle(FSM* fsm) {
    fsm->set_state(IdleState::instance());
}

void FSM::InitState::exit(FSM* fsm) {}

FSM::State& FSM::InitState::instance() {
    static InitState s;
    return s;
}

FSM::InitState::~InitState() {}

} // namespace raiju
