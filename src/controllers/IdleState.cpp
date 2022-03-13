#include "FSM.hpp"

namespace raiju {

void FSM::IdleState::enter(FSM *fsm) {}
void FSM::IdleState::cycle(FSM *fsm) {}
void FSM::IdleState::exit(FSM *fsm) {}

FSM::State &FSM::IdleState::instance() {
    static IdleState s;
    return s;
}

FSM::IdleState::~IdleState() {}

} // namespace raiju
