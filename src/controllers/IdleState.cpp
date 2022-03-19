#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

void FSM::IdleState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:idle");
    fsm->s_led.board_led_off();
}

void FSM::IdleState::cycle(FSM* fsm) {
    fsm->s_bt.transmit("s:idle");
    fsm->s_led.toggle_board_led();
    mcu::sleep(500);

    if (fsm->s_bt.data_available()) {
        auto packet = fsm->s_bt.last_read_packet();

        if (packet.byte1 == 0x01) {
            if (packet.byte2 == 0x01) {
                fsm->set_state(RCState::instance());
            }
        }
    }
}

void FSM::IdleState::exit(FSM* fsm) {}

FSM::State& FSM::IdleState::instance() {
    static IdleState s;
    return s;
}

FSM::IdleState::~IdleState() {}

} // namespace raiju
