#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

static uint32_t tick = 0;

FSM::AutoWaitState::AutoWaitState() {}

void FSM::AutoWaitState::enter(FSM* fsm) {
    fsm->s_bt.transmit("state:AUTOWAIT");
    tick = mcu::get_tick();
}

void FSM::AutoWaitState::cycle(FSM* fsm) {
    if (mcu::get_tick() - tick >= 200) {
        fsm->s_led.toggle_board_led();
        tick = mcu::get_tick();
    }

    if (fsm->s_smodule.is_start()) {
        fsm->set_state(StrategyState::instance());
        return;
    }
}

void FSM::AutoWaitState::exit(FSM* fsm) {
    fsm->s_led.board_led_on();
}

FSM::State& FSM::AutoWaitState::instance() {
    static AutoWaitState s;
    return s;
}

FSM::AutoWaitState::~AutoWaitState() {}

} // namespace raiju
