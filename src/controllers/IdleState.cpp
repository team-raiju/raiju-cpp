#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

static bool test = true;

void FSM::IdleState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:idle");
    fsm->s_led.board_led_off();
    fsm->s_driving.stop();
}

void FSM::IdleState::cycle(FSM* fsm) {
    if (!fsm->button.is_active()) {
        fsm->s_smodule.reset();
    }

    auto ch4 = fsm->s_radio.get_ch4();
    if (ch4 > 1250 && ch4 < 1750) {
        fsm->set_state(RCState::instance());
        return;
    }

    if (ch4 > 1750) {
        fsm->set_state(SensorCheckState::instance());
        return;
    }

    if (test) {
        test = false;

        for (int i = 0; i < 16; i++) {
            fsm->s_led.led_stripe.set_color(i, Color::purple());
            fsm->s_led.led_stripe.send();

            fsm->s_buzzer.beep(42);
            hal::mcu::sleep(42);
        }

        hal::mcu::sleep(200);
        fsm->s_buzzer.beep(600);
    }

    fsm->s_led.toggle_board_led();
    mcu::sleep(500);
}

void FSM::IdleState::exit(FSM* fsm) {
    fsm->s_led.board_led_off();
}

FSM::State& FSM::IdleState::instance() {
    static IdleState s;
    return s;
}

FSM::IdleState::~IdleState() {}

} // namespace raiju
