#include "FSM.hpp"
#include "config.hpp"
#include "utils.h"

namespace raiju {

static Strategy* strategies[] = {
    nullptr,
    &SmallStepsStrategy::instance(),
    &StarStrategy::instance(),
    &StartLeftStrategy::instance(),
    &StartRightStrategy::instance(),

};

FSM::FSM() {
    state = &InitState::instance();
    this->start_strategy_idx = 3;
    this->round_strategy_idx = 1;

    this->start_strategy = strategies[this->start_strategy_idx];
    this->round_strategy = strategies[this->round_strategy_idx];
}

void FSM::init() {
    this->state->enter(this);
}

void FSM::cycle() {
    process_bt();
    this->state->cycle(this);
}

void FSM::set_state(State& state) {
    this->state->exit(this);
    this->state = &state;
    this->state->enter(this);
}

void FSM::run_start_strategy() {
    this->start_strategy = strategies[this->start_strategy_idx];
    if (this->start_strategy != nullptr) {
        this->start_strategy->run(this);
    }
}

void FSM::run_round_strategy() {
    this->round_strategy = strategies[this->round_strategy_idx];
    if (this->round_strategy != nullptr) {
        this->round_strategy->run(this);
    }
}

void FSM::process_bt() {
    if (!this->s_bt.data_available()) {
        return;
    }

    auto packet = this->s_bt.last_read_packet();

    if (packet.is_data_request()) {
        report_config();
        return;
    }

    if (packet.is_state_swap_request()) {
        if (this->state != &IdleState::instance()) {
            this->set_state(IdleState::instance());
        } else {
            this->set_state(AutoWaitState::instance());
        }
        return;
    }

    config::enabledDistanceSensors = packet.enabledDistanceSensors;
    config::enabledLineSensors = packet.enabledLineSensors;
    config::maxMotorSpeed = packet.maxMotorSpeed;
    config::reverseSpeed = packet.reverseSpeed;
    config::reverseTimeMs = packet.reverseTimeMs;
    config::turnSpeed = packet.turnSpeed;
    config::turnTimeMs = packet.turnTimeMs;
    config::stepWaitTimeMs = packet.stepWaitTimeMs;

    if (packet.strategy < len(strategies)) {
        this->round_strategy_idx = packet.strategy;
        this->round_strategy = strategies[this->round_strategy_idx];
    }

    if (packet.preStrategy < len(strategies)) {
        this->start_strategy_idx = packet.preStrategy;
        this->start_strategy = strategies[this->start_strategy_idx];
    }
}

void FSM::report_config() {
    char buffer[20];

    for (size_t i = 0; i < len(strategies); i++) {
        snprintf(buffer, 20, "ss:%d:%s", i, i > 0 ? strategies[i]->name.c_str() : "-");
        this->s_bt.transmit(buffer);
        hal::mcu::sleep(10);
    }

    snprintf(buffer, 20, "sens:%hu:%hu", config::enabledDistanceSensors, config::enabledLineSensors);
    this->s_bt.transmit(buffer);
    hal::mcu::sleep(10);

    snprintf(buffer, 20, "rev:%hu:%hu", config::reverseSpeed, config::reverseTimeMs);
    this->s_bt.transmit(buffer);
    hal::mcu::sleep(10);

    snprintf(buffer, 20, "turn:%hu:%hu", config::turnSpeed, config::turnTimeMs);
    this->s_bt.transmit(buffer);
    hal::mcu::sleep(10);

    snprintf(buffer, 20, "step:%hu", config::stepWaitTimeMs);
    this->s_bt.transmit(buffer);
    hal::mcu::sleep(10);

    snprintf(buffer, 20, "str:%hu:%hu", this->start_strategy_idx, this->round_strategy_idx);
    this->s_bt.transmit(buffer);
    hal::mcu::sleep(10);

    snprintf(buffer, 20, "mms:%hu", config::maxMotorSpeed);
    this->s_bt.transmit(buffer);
    hal::mcu::sleep(10);
}

} // namespace raiju
