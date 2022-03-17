#include "FSM.hpp"

namespace raiju {

// static int led_num = 0;

void FSM::IdleState::enter(FSM* fsm) {
    // for (int i = 0; i < 16; i++) {
    //     fsm->leds.set_color(i, Color::white());
    //     hal::mcu::sleep(1000);
    // }
    fsm->s_buzzer.play_megalovania();
}

void FSM::IdleState::cycle(FSM* fsm) {
    fsm->s_led.toggle_board_led();

    // fsm->leds.set_color(led_num, Color{0, 0, 127});
    // fsm->leds.send();

    hal::mcu::sleep(300);

    // led_num++;
    // if (led_num > 15) {
    //     led_num = 0;
    //     fsm->leds.reset_all();
    // }
}
void FSM::IdleState::exit(FSM* fsm) {}

FSM::State& FSM::IdleState::instance() {
    static IdleState s;
    return s;
}

FSM::IdleState::~IdleState() {}

} // namespace raiju
