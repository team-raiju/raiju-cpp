#include "FSM.hpp"

namespace raiju {

FSM::FSM() : button(GPIOC, hal::GPIO::Pin::p15) {
    state = &InitState::instance();
}

void FSM::init() {
    this->state->enter(this);
}

void FSM::cycle() {
    this->state->cycle(this);
}

void FSM::set_state(State& state) {
    this->state->exit(this);
    this->state = &state;
    this->state->enter(this);
}

void FSM::set_start_strategy(Strategy& strategy) {
    this->start_strategy = &strategy;
}

void FSM::set_round_strategy(Strategy& strategy) {
    this->round_strategy = &strategy;
}

void FSM::run_start_strategy() {
    if (this->start_strategy != nullptr) {
        this->start_strategy->run(this, this->start_strategy_params);
    }
}

void FSM::run_round_strategy() {
    if (this->round_strategy != nullptr) {
        this->round_strategy->run(this, this->round_strategy_params);
    }
}

} // namespace raiju
