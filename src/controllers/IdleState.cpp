#include "utils.h"

#include "FSM.hpp"

namespace raiju {

// static int led_num = 0;

void FSM::IdleState::enter(FSM* fsm) {
    // for (int i = 0; i < 16; i++) {
    //     fsm->leds.set_color(i, Color::white());
    //     hal::mcu::sleep(1000);
    // }
    // fsm->s_led.test();
    // fsm->s_buzzer.play_megalovania();
    fsm->s_led.board_led_on();
}

void FSM::IdleState::cycle(FSM* fsm) {
    for (int i = 0; i < 100; i++) {
        fsm->s_driving.drive(i, i);
        hal::mcu::sleep(100);
    }

    for (int i = 100; i > -100; i--) {
        fsm->s_driving.drive(i, i);
        hal::mcu::sleep(100);
    }

    for (int i = -100; i < 0; i++) {
        fsm->s_driving.drive(i, i);
        hal::mcu::sleep(100);
    }
}

void FSM::IdleState::exit(FSM* fsm) {}

FSM::State& FSM::IdleState::instance() {
    static IdleState s;
    return s;
}

FSM::IdleState::~IdleState() {}

} // namespace raiju
