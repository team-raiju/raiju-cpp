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

    auto ch1 = fsm->s_radio.get_ch1();
    auto ch2 = fsm->s_radio.get_ch2();

   
    // fsm->s_led.led_stripe.set_color(i, Color::purple());
    // fsm->s_led.led_stripe.send();


    if ((ch1 < 1250)) {
        fsm->start_strategy_idx = 0; // None
    } else if ((ch1 > 1250) && (ch1 < 1750)) {
        fsm->start_strategy_idx = 3; // Left
    } else {
        fsm->start_strategy_idx = 4; // Right
    }

    if ((ch2 < 1250)) {
        fsm->s_led.led_stripe_set_all(Color{0, 0, 127});
        fsm->s_led.led_stripe_send();
        fsm->round_strategy_idx = 1; // Smale steps
    } else if ((ch2 > 1250) && (ch2 < 1750)) {
        fsm->s_led.led_stripe_set_all(Color{0, 127, 0});
        fsm->s_led.led_stripe_send();
        fsm->round_strategy_idx = 2; // Star
    } else {
        fsm->s_led.led_stripe_set_all(Color{127, 0, 0});
        fsm->s_led.led_stripe_send();
        fsm->round_strategy_idx = 2; // Star
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
