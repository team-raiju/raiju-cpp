#include "FSM.hpp"

namespace raiju {

void FSM::SensorCheckState::enter(FSM* fsm) {}

void FSM::SensorCheckState::cycle(FSM* fsm) {}

void FSM::SensorCheckState::exit(FSM* fsm) {}

FSM::State& FSM::SensorCheckState::instance() {
    static SensorCheckState s;
    return s;
}

FSM::SensorCheckState::~SensorCheckState() {}

} // namespace raiju
