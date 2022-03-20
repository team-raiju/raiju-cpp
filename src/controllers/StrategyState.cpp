#include "utils.h"

#include "FSM.hpp"

#define DIST_RIGHT 5
#define DIST_BRIGHT 6
#define DIST_FRONT 7
#define DIST_BLEFT 8
#define DIST_LEFT 9

namespace mcu = hal::mcu;

namespace raiju {

// TODO: isso deveria estar na classe, tirar a definição padrão State (o define) para poder colocar
// esse tipo de variável privada
static uint32_t ticker = 0; // TODO: Adapter > SoftTimer
static uint32_t ticker_fail = 0;
static bool still = false;
static bool leaving = false;

void FSM::StrategyState::enter(FSM* fsm) {
    fsm->s_bt.transmit("s:strategy");
    fsm->s_driving.stop();

    ticker = mcu::get_tick();
    ticker_fail = mcu::get_tick();

    fsm->s_led.led_stripe_set_all(Color{127, 0, 0});
    fsm->s_led.led_stripe_send();
}

void FSM::StrategyState::cycle(FSM* fsm) {
    // Leave via Start Module
    if (!fsm->s_smodule.is_start()) {
        fsm->set_state(IdleState::instance());
        return;
    }

    // Leave via controller
    auto ch4 = fsm->s_radio.get_ch4();
    if ((ch4 < 1750) && !leaving) {
        ticker_fail = mcu::get_tick();
        leaving = true;
    }

    if (ch4 >= 1750) {
        leaving = false;
    }

    if (leaving && mcu::get_tick() - ticker_fail >= 1000) {
        fsm->set_state(IdleState::instance());
        return;
    }

    // Strategy
    if (fsm->strategy != 1) {
        if (fsm->s_line.is_white(LineService::Position::FR1) || fsm->s_line.is_white(LineService::Position::FL1)) {
            fsm->s_driving.drive(-100, -100);
            mcu::sleep(150); // TODO: Calibração desses valores de tempo de volta pras curvas

            int8_t mult = fsm->s_line.is_white(LineService::Position::FR1) ? -1 : 1;
            fsm->s_driving.drive(100 * mult, -100 * mult);
            mcu::sleep(175);
        }
    }

    if (fsm->s_distance.is_reading(DIST_FRONT) ||
        (fsm->s_distance.is_reading(DIST_BRIGHT) && fsm->s_distance.is_reading(DIST_BLEFT)) || fsm->strategy == 2) {
        fsm->s_driving.drive(100, 100);
        still = false;
    } else if (fsm->s_distance.is_reading(DIST_BRIGHT)) {
        fsm->s_driving.drive(100, 30);
        still = false;
    } else if (fsm->s_distance.is_reading(DIST_BLEFT)) {
        fsm->s_driving.drive(30, 100);
        still = false;
    } else if (fsm->s_distance.is_reading(DIST_RIGHT)) {
        fsm->s_driving.drive(100, -100);
        still = false;
    } else if (fsm->s_distance.is_reading(DIST_LEFT)) {
        fsm->s_driving.drive(-100, 100);
        still = false;
    } else if (fsm->strategy == 4) {
        fsm->s_driving.drive(100, 100);
        still = false;
    } else {
        if (!still) {
            still = true;
            ticker = mcu::get_tick();
        }
        fsm->s_driving.drive(0, 0);
    }

    if (still && mcu::get_tick() - ticker >= 3000) {
        still = false;
        fsm->s_driving.drive(50, 50);
        mcu::sleep(100);
    }
}

void FSM::StrategyState::exit(FSM* fsm) {
    fsm->s_driving.stop();

    fsm->s_led.purple_charge();
}

FSM::State& FSM::StrategyState::instance() {
    static StrategyState s;
    return s;
}

FSM::StrategyState::~StrategyState() {}

} // namespace raiju
