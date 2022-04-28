#include "utils.h"

#include "FSM.hpp"

namespace raiju {

FSM::RCCheckState::RCCheckState() {}

void FSM::RCCheckState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:rccheck");
}

void FSM::RCCheckState::cycle(FSM* fsm) {
    fsm->s_driving.drive(20, 0);

    if (!fsm->button.is_active()) {
        fsm->set_state(IdleState::instance());
        return;
    }
}

void FSM::RCCheckState::exit(FSM* fsm) {}

FSM::State& FSM::RCCheckState::instance() {
    static RCCheckState s;
    return s;
}

FSM::RCCheckState::~RCCheckState() {}

} // namespace raiju
