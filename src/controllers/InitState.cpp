#include "utils.h"

#include "FSM.hpp"

namespace mcu = hal::mcu;

namespace raiju {

FSM::InitState::InitState() {}

void FSM::InitState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:init");

    fsm->s_driving.stop();
    fsm->s_line.start();

    // fsm->s_buzzer.play_megalovania();

    // fsm->s_led.purple_charge();
    // for (int i = 0; i < 16; i++) {
    //     fsm->s_led.led_stripe.set_color(i, Color::purple());
    //     fsm->s_led.led_stripe.send();

    //     fsm->s_buzzer.beep(42);
    //     hal::mcu::sleep(42);
    // }

    // hal::mcu::sleep(200);
    // fsm->s_buzzer.beep(600);
}

void FSM::InitState::cycle(FSM* fsm) {
    // fsm->set_state(SensorCheckState::instance());
    fsm->set_state(IdleState::instance());
}

void FSM::InitState::exit(FSM* fsm) {}

FSM::State& FSM::InitState::instance() {
    static InitState s;
    return s;
}

FSM::InitState::~InitState() {}

} // namespace raiju
