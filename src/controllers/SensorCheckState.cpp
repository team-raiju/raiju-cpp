#include "FSM.hpp"

#define DIST_RIGHT 5
#define DIST_BRIGHT 6
#define DIST_FRONT 7
#define DIST_BLEFT 8
#define DIST_LEFT 9

namespace raiju {

void FSM::SensorCheckState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:scheck");
    fsm->s_driving.stop();
}

void FSM::SensorCheckState::cycle(FSM* fsm) {
    if (fsm->s_smodule.is_start()) {
        fsm->set_state(StrategyState::instance());
        return;
    }

    auto ch3 = fsm->s_radio.get_ch3();
    fsm->s_led.led_stripe_reset();

    if (ch3 < 1200) {
        tester1 = 1;
        for (int i = 0; i < 8; i++) {
            fsm->s_led.led_stripe_set(i, Color{0, 127, 0});
        }
    } else if (ch3 < 1400) {
        tester1 = 2;
        for (int i = 0; i < 8; i++) {
            fsm->s_led.led_stripe_set(i, Color{0, 0, 127});
        }
    } else if (ch3 < 1600) {
        tester1 = 3;
        for (int i = 0; i < 8; i++) {
            fsm->s_led.led_stripe_set(i, Color{127, 127, 0});
        }
    } else if (ch3 < 1800) {
        tester1 = 4;
        for (int i = 8; i < 16; i++) {
            fsm->s_led.led_stripe_set(i, Color{0, 127, 0});
        }
    } else if (ch3 < 2000) {
        tester1 = 5;
        for (int i = 8; i < 16; i++) {
            fsm->s_led.led_stripe_set(i, Color{0, 0, 127});
        }
    }

    fsm->s_led.led_stripe_send();

    auto ch4 = fsm->s_radio.get_ch4();
    if (ch4 < 1750) {
        fsm->set_state(IdleState::instance());
        return;
    }

    uint8_t sensors[10] = {0};

    sensors[0] = fsm->s_line.is_white(LineService::FR1);
    sensors[1] = fsm->s_line.is_white(LineService::FL1);
    sensors[2] = fsm->s_line.is_white(LineService::BR);
    sensors[3] = fsm->s_line.is_white(LineService::BL);

    sensors[4] = 0x14;

    for (int i = 5; i <= 9; i++) {
        if (fsm->s_distance.is_reading(i)) {
            sensors[i] = 0xFF;
        }
    }

    fsm->s_bt.transmit((uint8_t*)sensors, 10);
    hal::mcu::sleep(50);
}

void FSM::SensorCheckState::exit(FSM* fsm) {}

FSM::State& FSM::SensorCheckState::instance() {
    static SensorCheckState s;
    return s;
}

FSM::SensorCheckState::~SensorCheckState() {}

} // namespace raiju
