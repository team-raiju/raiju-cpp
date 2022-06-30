#include "utils.h"

#include "FSM.hpp"
#include "debug.hpp"

namespace mcu = hal::mcu;

namespace raiju {

FSM::InitState::InitState() {}

void FSM::InitState::enter(FSM* fsm) {
    fsm->s_bt.transmit("state:INIT");

    fsm->s_driving.stop();
    fsm->s_line.start();

    DEBUG_LOG("INIT!");
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
