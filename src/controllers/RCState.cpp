#include "utils.h"

#include "FSM.hpp"

namespace raiju {

void FSM::RCState::enter(FSM* fsm) {}

void FSM::RCState::cycle(FSM* fsm) {}

void FSM::RCState::exit(FSM* fsm) {}

FSM::State& FSM::RCState::instance() {
    static RCState s;
    return s;
}

FSM::RCState::~RCState() {}

} // namespace raiju
