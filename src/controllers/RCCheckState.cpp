#include "utils.h"

#include "FSM.hpp"

namespace raiju {

void FSM::RCCheckState::enter(FSM* fsm) {}

void FSM::RCCheckState::cycle(FSM* fsm) {}

void FSM::RCCheckState::exit(FSM* fsm) {}

FSM::State& FSM::RCCheckState::instance() {
    static RCCheckState s;
    return s;
}

FSM::RCCheckState::~RCCheckState() {}

} // namespace raiju
