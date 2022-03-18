#include "utils.h"

#include "FSM.hpp"

namespace raiju {

void FSM::AutoWaitState::enter(FSM* fsm) {}

void FSM::AutoWaitState::cycle(FSM* fsm) {}

void FSM::AutoWaitState::exit(FSM* fsm) {}

FSM::State& FSM::AutoWaitState::instance() {
    static AutoWaitState s;
    return s;
}

FSM::AutoWaitState::~AutoWaitState() {}

} // namespace raiju
