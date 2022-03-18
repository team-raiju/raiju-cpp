#include "utils.h"

#include "FSM.hpp"

namespace raiju {

void FSM::InitState::enter(FSM* fsm) {
    fsm->s_led.board_led_on();
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
