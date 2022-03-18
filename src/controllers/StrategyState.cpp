#include "utils.h"

#include "FSM.hpp"

namespace raiju {

void FSM::StrategyState::enter(FSM* fsm) {}

void FSM::StrategyState::cycle(FSM* fsm) {}

void FSM::StrategyState::exit(FSM* fsm) {}

FSM::State& FSM::StrategyState::instance() {
    static StrategyState s;
    return s;
}

FSM::StrategyState::~StrategyState() {}

} // namespace raiju
