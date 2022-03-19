#include "utils.h"

#include "FSM.hpp"

namespace raiju {

void FSM::RCState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:rc");
}

void FSM::RCState::cycle(FSM* fsm) {
    auto coords = fsm->s_radio.coordinates();

    auto mot1 = coords.y + coords.x;
    auto mot2 = coords.y - coords.x;

    fsm->s_driving.drive(mot1, mot2);

    if (fsm->s_bt.data_available()) {
        auto packet = fsm->s_bt.last_read_packet();

        if (packet.byte1 == 0x01) {
            if (packet.byte2 == 0x02) {
                fsm->set_state(IdleState::instance());
            }
        }
    }
}

void FSM::RCState::exit(FSM* fsm) {
    fsm->s_driving.drive(0, 0);
}

FSM::State& FSM::RCState::instance() {
    static RCState s;
    return s;
}

FSM::RCState::~RCState() {}

} // namespace raiju
