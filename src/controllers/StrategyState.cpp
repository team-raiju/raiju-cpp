#include "utils.h"

#include "FSM.hpp"

#define DIST_RIGHT 5
#define DIST_BRIGHT 6
#define DIST_FRONT 7
#define DIST_BLEFT 8
#define DIST_LEFT 9

namespace mcu = hal::mcu;

namespace raiju {

FSM::StrategyState::StrategyState() : leaveTicker(1000) {
    this->leaving = false;
    this->ran_initial = false;
}

void FSM::StrategyState::enter(FSM* fsm) {
    fsm->s_bt.transmit("state:STRATEGY");
    fsm->s_driving.stop();

    leaveTicker.reset();
    ran_initial = false;

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
    if ((ch4 < CH4_HIGH_THRESHOLD) && !leaving) {
        leaveTicker.reset();
        leaving = true;
    }

    if (ch4 >= CH4_HIGH_THRESHOLD) {
        leaving = false;
    }

    if (leaving && leaveTicker.expired()) {
        fsm->set_state(IdleState::instance());
        return;
    }

    if (!ran_initial) {
        ran_initial = true;
        fsm->run_start_strategy();
    }

    fsm->run_round_strategy();
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
