#include "utils.h"

#include "FSM.hpp"

namespace raiju {

FSM::RCCheckState::RCCheckState() {}

void FSM::RCCheckState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:RCCHECK");
}

void FSM::RCCheckState::cycle(FSM* fsm) {}

void FSM::RCCheckState::exit(FSM* fsm) {}

FSM::State& FSM::RCCheckState::instance() {
    static RCCheckState s;
    return s;
}

FSM::RCCheckState::~RCCheckState() {}

} // namespace raiju
